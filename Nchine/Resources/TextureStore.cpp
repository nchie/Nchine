//
// Created by aejt on 11/23/17.
//

#include "TextureStore.h"

namespace Nchine {

    Resource<Texture2D> TextureStore::get(const std::string &name) {
        return m_cache.get_resource(name);
    }

    Resource<Texture2D> TextureStore::load(const std::string &name) {
        return m_cache.load(name, m_loader.load(name));
    }

    /*Resource<Texture2D> TextureStore::load_async(const std::string &name) {
        return Nchine::Resource<Nchine::Texture2D>(Nchine::Resource<Texture2D>());
    }*/
}