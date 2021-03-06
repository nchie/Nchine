//
// Created by aejt on 10/22/17.
//

#pragma once


#include <vector>

#include <bitset>

#include "glm/glm.hpp"


namespace Nchine {

    class Geometry {
        static const int ATTRIBUTE_COUNT = 8;
        static const int COLORS_BIT = 0;
        static const int TEXCOORDS_BIT = 1;
        static const int NORMALS_BIT = 2;
        static const int SKIN_BIT = 3;

    private:
        std::bitset<ATTRIBUTE_COUNT> m_attribute_data;
        unsigned int m_vao = 0;
        unsigned int m_vbo = 0;
        unsigned int m_ebo = 0;

        unsigned int m_vertice_count = 0;
        unsigned int m_indice_count = 0;

    public:
        Geometry(const std::vector<float> &vertice_data, const std::vector<unsigned int> &indices,
             std::bitset<ATTRIBUTE_COUNT> attributes);

        Geometry(const std::vector<glm::vec3> &vertices, const std::vector<unsigned int> &indices);

        Geometry(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv, const std::vector<unsigned int> &indices);

        Geometry(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv,
             const std::vector<glm::vec3> &normals, const std::vector<unsigned int> &indices);

        ~Geometry();

        // Copy constructors: deleted
        Geometry& operator=(const Geometry& other) = delete;
        Geometry(const Geometry& other) = delete;

        // Move constructors
        Geometry(Geometry&& other) noexcept;
        Geometry& operator=(Geometry&& other) noexcept;

        enum flags {
            none = 0,
            colors = 1 << COLORS_BIT,
            texcoords = 1 << TEXCOORDS_BIT,
            normals = 1 << NORMALS_BIT,
            skin = 1 << SKIN_BIT
        };

        void draw() const; //TODO: Remove

    private:
        void generate(const std::vector<float> &vertice_data, const std::vector<unsigned int> &indices);
        int get_stride() const;

    public: //Getters and setters
        unsigned int get_vao() const { return m_vao; }
        unsigned int get_vbo() const { return m_vbo; }
        unsigned int get_ebo() const { return m_ebo; }
        unsigned int get_vertice_count() const { return m_vertice_count; } // TODO: Make object hold actual vertices and make this one return .size() of that vector?
        unsigned int get_indice_count() const { return m_indice_count; } // TODO: Make object hold actual indices and make this one return .size() of that vector?
    };


}