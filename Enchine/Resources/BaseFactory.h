//
// Created by aejt on 11/16/17.
//

#pragma once

#include "BinaryFileLoader.h"

namespace Enchine {

    template<typename T>
    class ResourceCache;

    template<typename T>
    class BaseFactory {

    protected:
        ResourceCache<T> *m_cache;
        BinaryFileLoader *m_binary_loader;


    public:
        BaseFactory(BinaryFileLoader *binary_loader, ResourceCache<T> *cache) : m_binary_loader(binary_loader),
                                                                            m_cache(cache) { }





    };

}