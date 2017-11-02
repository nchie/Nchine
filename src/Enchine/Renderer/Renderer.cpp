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

    Renderer::Renderer() : m_active_target(&m_default_target)
    {

        resource_lib.dummy_load();

        test = resource_lib.get_mesh("Square");

        m_camera.set_perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        Material &mat1 = temp_materials.emplace_back(resource_lib.get_shader("DummyShader"));
        mat1.set_texture("texture1", resource_lib.get_texture("AwesomeFace"));
        mat1.set_texture("texture2", resource_lib.get_texture("Container2"));
        mat1.set_vector("color", glm::vec3(0.0f, 1.0f, 0.0f));

        Material &mat2 = temp_materials.emplace_back(resource_lib.get_shader("DummyShader2"));
        mat2.set_texture("texture1", resource_lib.get_texture("AwesomeFace"));
        mat2.set_texture("texture2", resource_lib.get_texture("Container2"));

    }


    void Renderer::render_command(const RenderCommand *command)
    {
        Material& material = command->material;
        Mesh& mesh = command->mesh;
        Resource<ShaderProgram>& program = material.get_program();

        glcontext.use_program(*program);

        // Set common uniforms TODO: Replace with UBOs!
        program->set_matrix("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, -2.0f)));

        for(const auto &uniform : material.get_uniforms())
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

        for(auto &sampler_uniform : material.get_sampler_uniforms())
        {
            // TODO: Should texture really bind itself?
            //sampler_uniforms.second.texture->bind(sampler_uniforms.second.unit);
            glcontext.bind_texture(sampler_uniform.second.unit, *sampler_uniform.second.texture);
        }

        glcontext.draw_mesh(mesh);
        //glBindVertexArray(mesh.get_vao());
        //glDrawElements(GL_TRIANGLES, mesh.get_indice_count(), GL_UNSIGNED_INT, 0);



    }

    void Renderer::run() {

        m_camera.update_view();
        m_uniform_buffer.projection = m_camera.get_projection();
        m_uniform_buffer.view = m_camera.get_view();
        m_uniform_buffer.view_projection = m_uniform_buffer.projection * m_uniform_buffer.view;
        //m_uniform_buffer.prev_view_projection = ?
        //m_uniform_buffer.inverse_view(glm::inverse(m_camera.get_view()));


        m_uniform_buffer.update();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        m_render_commands.emplace_back(RenderCommand {
                glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)),
                glm::mat4(1.0f), //?
                *(*test),
                temp_materials[1],
                glm::vec3(1.0f),
                glm::vec3(1.0f)
        });



        for (const auto &command : m_render_commands)
        {
            render_command(&command);
        }
        m_render_commands.clear();
    }

    void Renderer::set_target(RenderTarget& render_target, GLenum target) {
        m_active_target = &render_target;
        glBindFramebuffer(GL_FRAMEBUFFER, render_target.get_id());
    }

    RenderTarget& Renderer::get_active_render_target() {
        return *m_active_target;
    }

}