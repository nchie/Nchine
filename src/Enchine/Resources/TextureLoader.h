//
// Created by aejt on 11/16/17.
//

#pragma once


#include <queue>
#include <vector>
#include <cstddef>
#include <string>

#include "BinaryLoader.h"
#include "Texture2D.h"


namespace Enchine {
    class TextureLoader {

    private:
        std::queue<std::vector<std::byte> > m_to_be_loaded;
        BinaryLoader loader;


    public:


        void load_async(const std::string& path);
        Texture2D load(const std::string& path);


    };
}

