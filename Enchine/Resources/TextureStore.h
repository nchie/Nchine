//
// Created by aejt on 11/23/17.
//

#pragma once

#include <string>

#include "TextureLoader.h"
#include "BinaryLoader.h"
#include "ResourceCache.h"
#include "Texture2D.h"

namespace Enchine {

    class TextureStore {

    private:
        ResourceCache<Texture2D> m_cache;
        TextureLoader m_loader;

    public:
        explicit TextureStore(BinaryLoader *binary_loader) : m_cache([](std::string name){}){ }

        Resource<Texture2D> load(const std::string& name, const std::string& path);

    };

}

