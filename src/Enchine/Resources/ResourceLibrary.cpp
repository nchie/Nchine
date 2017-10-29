//
// Created by aejt on 10/29/17.
//

#define STB_IMAGE_IMPLEMENTATION // TODO: Remove
#include <stb_image.h> // TODO: Remove

#include "ResourceLibrary.h"

void Enchine::ResourceLibrary::dummy_load() {
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

    m_shader_cache.load("DummyShader", ShaderProgram(vertexShaderSource, fragmentShaderSource));
    m_mesh_cache.load("Square", Mesh(vertex_positions, texcoords, indices));
    unsigned char *data1 = stbi_load("resources/textures/awesomeface.png", &width, &height, &nr_channels, 0);
    m_texture_cache.load("AwesomeFace", Texture2D(reinterpret_cast<std::byte *>(data1), width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE));

    unsigned char *data2 = stbi_load("resources/textures/container2.png", &width, &height, &nr_channels, 0);
    m_texture_cache.load("Container2", Texture2D(reinterpret_cast<std::byte *>(data2), width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE));

    stbi_image_free(data1);
    stbi_image_free(data2);

}

Enchine::Resource<Enchine::ShaderProgram> Enchine::ResourceLibrary::get_shader(std::string name) {
    return m_shader_cache.get_resource(name);
}

Enchine::Resource<Enchine::Texture2D> Enchine::ResourceLibrary::get_texture(std::string name) {
    return m_texture_cache.get_resource(name);
}

Enchine::Resource<Enchine::Mesh> Enchine::ResourceLibrary::get_mesh(std::string name) {
    return m_mesh_cache.get_resource(name);
}
