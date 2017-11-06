//
// Created by aejt on 10/22/17.
//

#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <variant>

namespace Enchine {

    // TODO: Remove this if not needed later on?
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    class GLFWwindow;

    Renderer::Renderer() : m_default_target(m_width, m_height),
                           m_active_target(&m_default_target),
                           m_gbuffer(m_width, m_height, true, {{GL_COLOR_ATTACHMENT0, GL_UNSIGNED_BYTE}, // Albedo
                                                               {GL_COLOR_ATTACHMENT1, GL_UNSIGNED_BYTE}, // Normals
                                                               {GL_COLOR_ATTACHMENT2, GL_FLOAT},         // Specular
                                                               {GL_COLOR_ATTACHMENT3, GL_FLOAT}})        // Diffuse?
    {

        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);


        resource_lib.dummy_load();


        m_camera.set_perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        Material &mat1 = temp_materials.emplace_back(resource_lib.get_shader("DummyShader"));
        mat1.set_texture("texture1", resource_lib.get_texture("Diffuse"));
        mat1.set_texture("texture2", resource_lib.get_texture("Container2"));
        mat1.set_vector("color", glm::vec3(0.0f, 1.0f, 0.0f));

        Material &mat2 = temp_materials.emplace_back(resource_lib.get_shader("DummyShader2"));
        mat2.set_texture("texture1", resource_lib.get_texture("Container2"));
        mat2.set_texture("texture2", resource_lib.get_texture("Diffuse"));

        Material &deferredGeometry = temp_materials.emplace_back(resource_lib.get_shader("DeferredGeometryShader"));
        deferredGeometry.set_texture("texture_diffuse1", resource_lib.get_texture("Diffuse"));
        deferredGeometry.set_texture("texture_specular1", resource_lib.get_texture("Specular"));

        Material &deferred = temp_materials.emplace_back(resource_lib.get_shader("DeferredShader"));
        deferred.set_texture("texture1", resource_lib.get_texture("Diffuse"));

        /*Material &deferred = temp_materials.emplace_back(resource_lib.get_shader("DeferredShader"));
        mat2.set_texture("texture_diffuse1", resource_lib.get_texture("Diffuse"));
        mat2.set_texture("texture_specular1", resource_lib.get_texture("Specular"));*/

        for(int i = 0; i < 1; i++)
        {
            for(int k = 0; k < 1; k++)
            {
                temp_render_commands.emplace_back(RenderCommand {
                        glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, k)),
                        glm::mat4(1.0f), //?
                        &(*resource_lib.get_mesh("Cube")),
                        &temp_materials[2],
                        glm::vec3(1.0f),
                        glm::vec3(1.0f)
                });
            }
        }

    }


    void Renderer::render_command(const RenderCommand *command)
    {
        Material* material = command->material;
        Mesh* mesh = command->mesh;
        Resource<ShaderProgram>& program = material->get_program();


        glcontext.use_program(*program);


        // Set common uniforms TODO: Replace with UBOs!
        //program->set_vector("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
        program->set_vector("lightPos", m_camera.get_position());
        program->set_vector("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        program->set_vector("objectColor", glm::vec3(0.0f, 0.8f, 0.31f));
        program->set_vector("viewPos", m_camera.get_position());


        program->set_matrix("model", command->transform);

        for(const auto &uniform : material->get_uniforms())
        {
            // C++17 magic switch case! TODO: Make this thing not as ugly!? Change to SWITCH-case with enums because it's probably more performant?
            std::visit(overloaded {
                    [&](auto arg)       { }, // Default: Do nothing
                    [&](bool arg)       { program->set_bool(uniform.first, arg);  },
                    [&](int arg)        { program->set_int(uniform.first, arg);  },
                    [&](float arg)      { program->set_bool(uniform.first, arg);  },
                    [&](glm::vec2 arg)  { program->set_vector(uniform.first, arg);  },
                    [&](glm::vec3 arg)  { program->set_vector(uniform.first, arg);  },
                    [&](glm::vec4 arg)  { program->set_vector(uniform.first, arg);  },
                    [&](glm::mat2 arg)  { program->set_matrix(uniform.first, arg);  },
                    [&](glm::mat3 arg)  { program->set_matrix(uniform.first, arg);  },
                    [&](glm::mat4 arg)  { program->set_matrix(uniform.first, arg);  },

            }, uniform.second.value);
        }

        for(auto &sampler_uniform : material->get_sampler_uniforms())
        {
            // TODO: Should texture really bind itself?
            //sampler_uniforms.second.texture->bind(sampler_uniforms.second.unit);
            glcontext.bind_texture(sampler_uniform.second.unit, *sampler_uniform.second.texture);
        }

        glcontext.draw_mesh(*mesh);
    }

    void Renderer::run() {

        glEnable(GL_DEPTH_TEST); // TODO: Fix cache
        glDepthFunc(GL_LESS);


        m_camera.update_view();
        m_uniform_buffer.projection = m_camera.get_projection();
        m_uniform_buffer.view = m_camera.get_view();
        m_uniform_buffer.view_projection = m_uniform_buffer.projection * m_uniform_buffer.view;
        m_uniform_buffer.inverse_projection = glm::inverse(m_uniform_buffer.projection);
        //m_uniform_buffer.prev_view_projection = ?
        m_uniform_buffer.inverse_view = glm::inverse(m_camera.get_view());

        m_uniform_buffer.update();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_render_commands = temp_render_commands;

        /* GEOMETRY PASS */
        set_target(m_gbuffer);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const auto &command : m_render_commands)
        {
            render_command(&command);
        }
        m_render_commands.clear();





        /* DEFERRED PASS */
        set_target(m_default_target);

        auto& deferred_shader = *resource_lib.get_shader("DeferredShader");

        glcontext.use_program(deferred_shader);
        glcontext.bind_texture(deferred_shader.get_sampler_slot("albedo"), m_gbuffer.get_color_texture(0));
        glcontext.bind_texture(deferred_shader.get_sampler_slot("normal"), m_gbuffer.get_color_texture(1));
        glcontext.bind_texture(deferred_shader.get_sampler_slot("depth"), m_gbuffer.get_depth_stencil_texture());
        //glcontext.bind_texture(deferred_shader.get_sampler_slot("texture1"), m_gbuffer.get_color_texture(2));
        glcontext.draw_mesh(*resource_lib.get_mesh("Quad"));

        //glReadBuffer(GL_COLOR_ATTACHMENT0);
        //blit_color(m_default_target, m_gbuffer);

    }

    void Renderer::set_target(RenderTarget& render_target, GLenum target) {
        m_active_target = &render_target;
        glBindFramebuffer(GL_FRAMEBUFFER, render_target.get_id());
    }

    RenderTarget& Renderer::get_active_render_target() {
        return *m_active_target;
    }

    void Renderer::blit_color(const RenderTarget &dst, const RenderTarget &src) {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, src.get_id());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst.get_id());
        glBlitFramebuffer(
                0, 0, src.get_width(), src.get_height(), 0, 0, dst.get_width(), dst.get_height(), GL_COLOR_BUFFER_BIT, GL_NEAREST
        );
        glBindFramebuffer(GL_FRAMEBUFFER, dst.get_id()); // TODO: Should this really bind to the default fb?
    }


}