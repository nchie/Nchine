//
// Created by aejt on 10/22/17.
//

#include "Renderer.h"

#include <glad/glad.h>

//#define STB_IMAGE_IMPLEMENTATION // TODO: Remove
//#include <stb_image.h> // TODO: Remove
#include <glm/gtc/matrix_transform.hpp>
#include <variant>


namespace Enchine {

    // TODO: Remove this if not needed later on?
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    class GLFWwindow;

// TODO: Ta bort
    const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            //"layout (location = 1) in vec3 aColor;\n"
            "layout (location = 1) in vec2 aTexCoord;\n"
            "\n"
            //"out vec3 ourColor;\n"
            "out vec2 TexCoord;\n"
            "\n"
            "uniform mat4 transform;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position =  transform * vec4(aPos, 1.0);\n"
            //"   ourColor = aColor;\n"
            "   TexCoord = aTexCoord;\n"
            "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            //"in vec3 ourColor;\n"
            "in vec2 TexCoord;\n"
            "uniform sampler2D texture1;\n"
            "uniform sampler2D texture2;\n"
            "uniform vec3 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.8) * vec4(color, 0.2);\n"
            "}\n\0";

    Renderer::Renderer() {

        resource_lib.dummy_load();

        temp_materials.emplace_back(&(*resource_lib.get_shader("DummyShader")));
    }


    void Renderer::render_command(const RenderCommand *command)
    {
        Material *material = command->material;
        Mesh *mesh = command->mesh;

        ShaderProgram *program = material->get_program();

        program->use();

        //material->m_texture->bind(2); // TODO: Remove
        //program->set_int("ourTexture3", 2); // TODO: Remove

        // Set common uniforms TODO: Replace with UBOs!
        program->set_matrix("transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)));

        for(const auto &uniform : material->get_uniforms())
        {
            // C++17 magic switch case! TODO: Make this thing not as ugly!?
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

        for(const auto &sampler_uniforms : material->get_sampler_uniforms())
        {
            sampler_uniforms.second.texture->bind(sampler_uniforms.second.unit);
        }

        glBindVertexArray(mesh->get_vao());
        glDrawElements(GL_TRIANGLES, mesh->get_indice_count(), GL_UNSIGNED_INT, 0);



    }

    void Renderer::run() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        temp_materials[0].set_texture("texture1", &(*resource_lib.get_texture("AwesomeFace")), 0);
        temp_materials[0].set_texture("texture2", &(*resource_lib.get_texture("Container2")), 1);
        temp_materials[0].set_vector("color", glm::vec3(0.0f, 1.0f, 0.0f));


        m_render_commands.emplace_back(RenderCommand {
                glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)),
                glm::mat4(1.0f), //?
                &(*resource_lib.get_mesh("Square")),
                &temp_materials[0],
                glm::vec3(1.0f),
                glm::vec3(1.0f)
        });


        for (const auto &command : m_render_commands)
        {
            render_command(&command);
        }
    }

}