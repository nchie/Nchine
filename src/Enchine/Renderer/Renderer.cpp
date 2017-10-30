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

    Renderer::Renderer() {

        resource_lib.dummy_load();

        Material &mat1 = temp_materials.emplace_back(resource_lib.get_shader("DummyShader"));
        mat1.set_texture("texture1", 0, resource_lib.get_texture("AwesomeFace"));
        mat1.set_texture("texture2", 1, resource_lib.get_texture("Container2"));
        mat1.set_vector("color", glm::vec3(0.0f, 1.0f, 0.0f));

        Material &mat2 = temp_materials.emplace_back(resource_lib.get_shader("DummyShader"));
        mat2.set_texture("texture1", 0, resource_lib.get_texture("AwesomeFace"));
        mat2.set_texture("texture2", 1, resource_lib.get_texture("Container2"));
        mat2.set_vector("color", glm::vec3(0.0f, 0.0f, 1.0f));
    }


    void Renderer::render_command(const RenderCommand *command)
    {
        Material& material = command->material;
        Mesh& mesh = command->mesh;
        Resource<ShaderProgram>& program = material.get_program();

        glcontext.use_program(*program);
        //program->use();


        // Set common uniforms TODO: Replace with UBOs!
        program->set_matrix("transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)));

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

        for(auto &sampler_uniforms : material.get_sampler_uniforms())
        {
            // TODO: Should texture really bind itself?
            //sampler_uniforms.second.texture->bind(sampler_uniforms.second.unit);

            //program->set_int(sampler_uniforms.first, sampler_uniforms.second.unit);

            glcontext.bind_texture(*sampler_uniforms.second.texture, sampler_uniforms.second.unit);
        }

        glcontext.draw_mesh(mesh);
        //glBindVertexArray(mesh.get_vao());
        //glDrawElements(GL_TRIANGLES, mesh.get_indice_count(), GL_UNSIGNED_INT, 0);



    }

    void Renderer::run() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        m_render_commands.emplace_back(RenderCommand {
                glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)),
                glm::mat4(1.0f), //?
                *resource_lib.get_mesh("Square"),
                temp_materials[0],
                glm::vec3(1.0f),
                glm::vec3(1.0f)
        });


        for (const auto &command : m_render_commands)
        {
            render_command(&command);
        }
    }

}