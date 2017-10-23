//
// Created by aejt on 10/22/17.
//

#pragma once


#include <vector>

#include <bitset>

#include "glm/glm.hpp"


namespace Enchine {

    class Mesh {
        static const int ATTRIBUTE_COUNT = 8;
        static const int COLORS_BIT = 0;
        static const int TEXCOORDS_BIT = 1;
        static const int NORMALS_BIT = 2;
        static const int SKIN_BIT = 3;

    private:
        std::bitset<ATTRIBUTE_COUNT> m_attribute_data;
        unsigned int m_vao;
        unsigned int m_vertice_count;
        unsigned int m_indice_count;

    public:
        Mesh(const std::vector<float> &vertice_data, const std::vector<int> &indices,
             std::bitset<ATTRIBUTE_COUNT> attributes);

        Mesh(const std::vector<glm::vec3> &vertices, const std::vector<int> &indices);

        Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv, const std::vector<int> &indices);

        Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv,
             const std::vector<glm::vec3> &normals, const std::vector<int> &indices);

        enum flags {
            none = 0,
            colors = 1 << COLORS_BIT,
            texcoords = 1 << TEXCOORDS_BIT,
            normals = 1 << NORMALS_BIT,
            skin = 1 << SKIN_BIT
        };

        void draw() const; //TODO: Remove

    private:
        void generate(const std::vector<float> &vertice_data, const std::vector<int> &indices);

        int get_stride() const;
    };


}