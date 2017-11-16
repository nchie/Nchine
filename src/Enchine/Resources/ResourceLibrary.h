//
// Created by aejt on 10/29/17.
//

#pragma once

#include "ResourceCache.h"
#include "ResourceLoader.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Geometry.h"
#include "ModelLoader.h"
#include "TextureLoader.h"
#include "BinaryLoader.h"




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
        ResourceCache<Geometry>      m_geometry_cache;
        ResourceLoader               m_resource_loader;
        TextureLoader                m_texture_loader;


        ModelLoader                  m_model_loader;


    public:
        ResourceLibrary() : m_shader_cache(dummy_load_extern),
                            m_texture_cache(dummy_load_extern),
                            m_geometry_cache(dummy_load_extern),
                            m_model_loader(this){ }
        void dummy_load();

        Resource<ShaderProgram> get_shader(std::string name);
        Resource<Texture2D> get_texture(std::string name);
        Resource<Geometry> get_mesh(std::string name);

        Resource<ShaderProgram> store_shader(const std::string &name, ShaderProgram &&shader) { return m_shader_cache.load(name, std::move(shader)); }
        Resource<Texture2D> store_texture(const std::string &name, Texture2D &&texture) { return m_texture_cache.load(name, std::move(texture)); }
        Resource<Geometry> store_geometry(const std::string &name, Geometry &&geometry) { return m_geometry_cache.load(name, std::move(geometry)); }

        SceneNode load_model(const std::string& path) { return m_model_loader.load_model(path); }



    };
}

