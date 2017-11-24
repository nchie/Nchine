//
// Created by aejt on 11/23/17.
//

#include "TextureStore.h"

namespace Enchine {

    Resource<Texture2D> TextureStore::get(const std::string &name) {
        return m_cache.get_resource(name);
    }

    Resource<Texture2D> TextureStore::load(const std::string &name) {
        return m_cache.load(name, m_loader.load(name));
    }

    /*Resource<Texture2D> TextureStore::load_async(const std::string &name) {
        return Enchine::Resource<Enchine::Texture2D>(Enchine::Resource<Texture2D>());
    }*/
}