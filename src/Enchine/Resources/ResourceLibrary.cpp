//
// Created by aejt on 10/29/17.
//

#define STB_IMAGE_IMPLEMENTATION // TODO: Remove
#include <stb_image.h> // TODO: Remove
#include "TestResources/TestShader1.h"
#include "TestResources/DeferredShader.h"
#include "TestResources/TestCube.h"
#include "TestResources/TestQuad.h"


#include "ResourceLibrary.h"


// TODO: Ta bort
void Enchine::ResourceLibrary::dummy_load() {
    stbi_set_flip_vertically_on_load(true);


    m_shader_cache.load("DeferredGeometryShader", ShaderProgram(vertexGeometryShader, fragmentGeometryShader, {"texture_diffuse1", "texture_specular1"}));
    m_shader_cache.load("DeferredShader", ShaderProgram(vertexDeferredShader, fragmentDeferredShader, {"albedo", "normal", "specular", "diffuse", "depth"}));
    m_shader_cache.load("DummyShader", ShaderProgram(vertexShaderSourcePerspective, fragmentShaderSourcePerspective, {"texture1", "texture2"}));
    m_shader_cache.load("DummyShader2", ShaderProgram(vertexShaderSourcePerspective, fragmentShaderSourcePerspective, {"texture1", "texture2"}));
    //dummy_shader->use(); // Should this be necessary?
    //dummy_shader->add_sampler("texture1");
    //dummy_shader->add_sampler("texture2");


    m_mesh_cache.load("Cube", Mesh(cube_positions, cube_texcoords, cube_normals, cube_indices));
    m_mesh_cache.load("Quad", Mesh(quad_positions, quad_texcoords, quad_indices));


    unsigned char *data;
    int width, height, nr_channels;
    data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nr_channels, 0);
    m_texture_cache.load("AwesomeFace", Texture2D(reinterpret_cast<std::byte*>(data), width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE));
    stbi_image_free(data);

    data = stbi_load("resources/textures/container2.png", &width, &height, &nr_channels, 0);
    m_texture_cache.load("Container2", Texture2D(reinterpret_cast<std::byte*>(data), width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE));
    stbi_image_free(data);

    data = stbi_load("resources/textures/photosculpt-orangestonewall-diffuse.jpg", &width, &height, &nr_channels, 0);
    m_texture_cache.load("Diffuse", Texture2D(reinterpret_cast<std::byte*>(data), width, height, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE));
    stbi_image_free(data);

    data = stbi_load("resources/textures/photosculpt-orangestonewall-normal.jpg", &width, &height, &nr_channels, 0);
    m_texture_cache.load("Normal", Texture2D(reinterpret_cast<std::byte*>(data), width, height, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE));
    stbi_image_free(data);

    data = stbi_load("resources/textures/photosculpt-orangestonewall-specular.jpg", &width, &height, &nr_channels, 0);
    m_texture_cache.load("Specular", Texture2D(reinterpret_cast<std::byte*>(data), width, height, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE));
    stbi_image_free(data);




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
