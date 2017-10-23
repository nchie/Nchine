//
// Created by aejt on 10/22/17.
//

#include "Renderer.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION // TODO: Remove
#include <stb_image.h> // TODO: Remove


namespace Enchine {

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
            "uniform sampler2D ourTexture;\n"
            "uniform sampler2D ourTexture2;\n"
            "uniform sampler2D ourTexture3;\n"
            "void main()\n"
            "{\n"
            "   FragColor = texture(ourTexture3, TexCoord);\n"
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
        unsigned char *data;
        data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nr_channels, 0);

        //temp_meshes.emplace_back(vertices, indices, Mesh::flags::colors | Mesh::flags::texcoords);
        //temp_meshes.emplace_back(vertices, indices, Mesh::flags::texcoords);

        temp_meshes.emplace_back(vertex_positions, texcoords, indices);
        temp_shaders.emplace_back(vertexShaderSource, fragmentShaderSource);

        temp_textures.emplace_back(reinterpret_cast<std::byte *>(data), width, height);

        stbi_image_free(data);
        data = stbi_load("resources/textures/container2.png", &width, &height, &nr_channels, 0);

        temp_textures.emplace_back(reinterpret_cast<std::byte *>(data), width, height);

        temp_materials.emplace_back(&temp_shaders[0], &temp_textures[0]);

        stbi_image_free(data);
    }

    Renderer::~Renderer() {

    }

    void Renderer::run() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);




        /*temp_materials[0].use();
        for (const auto &mesh : temp_meshes)
            mesh.draw();*/


    }

}