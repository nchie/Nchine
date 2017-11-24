//
// Created by aejt on 10/29/17.
//

#pragma once

#include "ResourceCache.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Geometry.h"
#include "ModelLoader.h"
#include "TextureLoader.h"
#include "BinaryFileLoader.h"
#include "TextureStore.h"




namespace Enchine
{
    // TODO: Ta bort
    static void dummy_load_extern(std::string name)
    {

    }


    class ResourceLibrary {

    private:
        ResourceCache<ShaderProgram> m_shader_cache; // TODO: Replace in favor of ShaderStore
        ResourceCache<Geometry>      m_geometry_cache; // TODO: Replace in favor of GeometryStore

        TextureStore                m_texture_store;


        ModelLoader                  m_model_loader;


    public:
        ResourceLibrary() : m_shader_cache(dummy_load_extern),
                            m_geometry_cache(dummy_load_extern),
                            m_model_loader(this){ }
        void dummy_load();

        Resource<ShaderProgram> get_shader(const std::string &name);
        Resource<Texture2D> get_texture(const std::string &name);
        Resource<Geometry> get_mesh(const std::string &name);

        Resource<Texture2D> store_texture(const std::string &name) { return m_texture_store.load(name); }

        Resource<ShaderProgram> store_shader(const std::string &name, ShaderProgram &&shader) { return m_shader_cache.load(name, std::move(shader)); }
        Resource<Geometry> store_geometry(const std::string &name, Geometry &&geometry) { return m_geometry_cache.load(name, std::move(geometry)); }

        SceneNode load_model(const std::string& path) { return m_model_loader.load_model(path); }



    };
}

