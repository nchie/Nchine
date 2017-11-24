//
// Created by aejt on 11/23/17.
//

#pragma once

#include <string>

#include "TextureLoader.h"
#include "BinaryFileLoader.h"
#include "ResourceCache.h"
#include "Texture2D.h"

namespace Enchine {

    class TextureStore {

    private:
        ResourceCache<Texture2D> m_cache;
        TextureLoader m_loader;

    public:
        TextureStore() : m_cache([](std::string name){}) { }; // TODO: Remove this
        explicit TextureStore(BinaryFileLoader *binary_loader) : m_cache([](std::string name){}){ }

        Resource<Texture2D> get(const std::string& name);

        Resource<Texture2D> load(const std::string& name);
        Resource<Texture2D> load_async(const std::string& name);

    };

}

