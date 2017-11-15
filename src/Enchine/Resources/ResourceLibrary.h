//
// Created by aejt on 10/29/17.
//

#pragma once

#include "ResourceCache.h"
#include "ResourceLoader.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Geometry.h"




namespace Enchine
{
    // TODO: Ta bort
    static void dummy_load_extern(std::string name)
    {

    }


    class ResourceLibrary {

    private:
        ResourceCache<ShaderProgram> m_shader_cache;
        ResourceCache<Texture2D>     m_texture_cache;
        ResourceCache<Geometry>          m_mesh_cache;
        ResourceLoader       m_resource_loader;

    public:
        ResourceLibrary() : m_shader_cache(dummy_load_extern),
                            m_texture_cache(dummy_load_extern),
                            m_mesh_cache(dummy_load_extern) { }
        void dummy_load();

        Resource<ShaderProgram> get_shader(std::string name);
        Resource<Texture2D> get_texture(std::string name);
        Resource<Geometry> get_mesh(std::string name);


    };
}

