//
// Created by aejt on 10/22/17.
//

#include "Renderer.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION // TODO: Remove
#include <stb_image.h> // TODO: Remove
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
            "void main()\n"
            "{\n"
            "   FragColor = texture(texture1, TexCoord) * texture(texture2, TexCoord);\n"
            "}\n\0";

    Renderer::Renderer() {
        std::vector<float> vertices = {
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // top right
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // top left
        };

        std::vector<glm::vec3> vertex_positions = {
                {0.5f,  0.5f,  0.0f},
                {0.5f,  -0.5f, 0.0f},
                {-0.5f, -0.5f, 0.0f},
                {-0.5f, 0.5f,  0.0f}
        };


        std::vector<glm::vec2> texcoords = {
                {1.0f, 1.0f},  // top right
                {1.0f, 0.0f},  // bottom right
                {0.0f, 0.0f},  // bottom left
                {0.0f, 1.0f}  // top left
        };

        std::vector<int> indices = {  // note that we start from 0!
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
        };


        stbi_set_flip_vertically_on_load(true);

        int width, height, nr_channels;
        unsigned char *data1 = stbi_load("resources/textures/awesomeface.png", &width, &height, &nr_channels, 0);

        temp_meshes.emplace_back(vertex_positions, texcoords, indices);
        temp_shaders.emplace_back(vertexShaderSource, fragmentShaderSource);
        temp_textures.emplace_back(reinterpret_cast<std::byte *>(data1), width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

        unsigned char *data2 = stbi_load("resources/textures/container2.png", &width, &height, &nr_channels, 0);

        temp_textures.emplace_back(reinterpret_cast<std::byte *>(data2), width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

        Material &material = temp_materials.emplace_back(&temp_shaders[0], &temp_textures[0]);

        //material.set_matrix("transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)));

        stbi_image_free(data1);
        stbi_image_free(data2);
    }

    Renderer::~Renderer()
    {

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

        temp_materials[0].set_texture("texture1", &temp_textures[0], 0);
        temp_materials[0].set_texture("texture2", &temp_textures[1], 1);

        m_render_commands.emplace_back(RenderCommand {
                glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)),
                glm::mat4(1.0f), //?
                &temp_meshes[0],
                &temp_materials[0],
                glm::vec3(1.0f),
                glm::vec3(1.0f)
        });


        for (const auto &command : m_render_commands)
        {
            render_command(&command);
        }

        //temp_materials[0].use();
        //for (const auto &mesh : temp_meshes)
        //    mesh.draw();


    }

}