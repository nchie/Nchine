//
// Created by aejt on 11/16/17.
//

#pragma once

#include "BaseFactory.h"
#include "Texture2D.h"
#include "ResourceCache.h"

namespace Enchine {

    class TextureFactory : public BaseFactory<Texture2D> {

    private:

    public:
        TextureFactory(BinaryFileLoader *binary_loader, ResourceCache<Texture2D> *cache) : BaseFactory<Texture2D>(binary_loader, cache) { }

        Resource<Texture2D> load(const std::string& path);
        void load_async(const std::string& path);

    };
}