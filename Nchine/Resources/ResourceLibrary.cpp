//
// Created by aejt on 10/29/17.
//

#define STB_IMAGE_IMPLEMENTATION // TODO: Remove
#include <stb_image.h> // TODO: Remove
#include "TestResources/TestShader1.h"
#include "TestResources/SSAOShader.h"
#include "TestResources/DeferredShader.h"
#include "TestResources/DeferredAmbientShader.h"
#include "TestResources/DeferredPointShader.h"
#include "TestResources/TestCube.h"
#include "TestResources/TestQuad.h"


#include "ResourceLibrary.h"


namespace Nchine {

// TODO: Ta bort
    void ResourceLibrary::dummy_load() {
        stbi_set_flip_vertically_on_load(true);


        m_shader_cache.load("DeferredGeometryShader", ShaderProgram(vertexGeometryShader, fragmentGeometryShader,
                                                                    {"texture_diffuse1", "texture_specular1"}));
        m_shader_cache.load("DeferredAmbientShader",
                            ShaderProgram(vertexDeferredAmbientShader, fragmentDeferredAmbientShader,
                                          {"gDiffuseSpecular", "gNormal", "gDepth"}));
        m_shader_cache.load("DeferredPointShader", ShaderProgram(vertexDeferredPointShader, fragmentDeferredPointShader,
                                                                 {"gDiffuseSpecular", "gNormal", "gDepth"}));
        m_shader_cache.load("SSAOShader", ShaderProgram(vertexSSAOShader, fragmentSSAOShader,
                                                        {"gDiffuseSpecular", "gNormal", "gDepth"}));


        m_geometry_cache.load("Cube", Geometry(cube_positions, cube_texcoords, cube_normals, cube_indices));
        m_geometry_cache.load("Quad", Geometry(quad_positions, quad_texcoords, quad_indices));
    }

    Resource<ShaderProgram> ResourceLibrary::get_shader(const std::string &name) {
        return m_shader_cache.get_resource(name);
    }

    Resource<Texture2D> ResourceLibrary::get_texture(const std::string &name) {
        //return m_texture_cache.get_resource(name);
        return m_texture_store.get(name);
    }

    Resource<Geometry> ResourceLibrary::get_mesh(const std::string &name) {
        return m_geometry_cache.get_resource(name);
    }

}