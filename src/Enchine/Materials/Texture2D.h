//
// Created by aejt on 10/22/17.
//

#pragma once

#include <cstddef>

namespace Enchine {
    class Texture2D {
    private:
        unsigned int m_texture_id;
        int width;
        int height;

    public:
        Texture2D(std::byte* data, int width, int height);

        unsigned int id() { return m_texture_id; }

        void bind(int uint);

    };
}


