//
// Created by aejt on 10/22/17.
//

#pragma once

#include <cstddef>

#include <glad/glad.h>

namespace Enchine {
    class Texture2D {
    private:
        unsigned int m_id;
        int m_width              = 0;
        int m_height             = 0;
        GLenum m_internal_format = GL_RGBA;
        GLenum m_format          = GL_RGBA;
        GLenum m_type            = GL_UNSIGNED_BYTE;

        bool m_mipmapping        = true;
        GLenum m_filter_min      = GL_LINEAR;
        GLenum m_filter_max      = GL_LINEAR;
        GLenum m_wrap_s          = GL_REPEAT;
        GLenum m_wrap_t          = GL_REPEAT;

    public:
        Texture2D();
        Texture2D(std::byte* data, int width, int height, GLenum internal_format, GLenum format, GLenum type);

        void generate(std::byte* data, int width, int height, GLenum internal_format, GLenum format, GLenum type);

        void bind(int uint=0);
        void unbind();

    public: // Getters and setters
        unsigned int get_id() const { return m_id; }
        bool         get_mipmapping() const { return m_mipmapping; }
        GLenum       get_filter_min() const  { return m_filter_min; }
        GLenum       get_filter_max() const  { return m_filter_max; }
        GLenum       get_wrap_s() const { return m_wrap_s; }
        GLenum       get_wrap_t() const { return m_wrap_t; }

        void    set_mipmapping(bool m_mipmapping) { m_mipmapping = m_mipmapping; }
        void    set_filter_min(GLenum m_filter_min) { m_filter_min = m_filter_min; }
        void    set_filter_max(GLenum m_filter_max) { m_filter_max = m_filter_max; }
        void    set_wrap_s(GLenum m_wrap_s) { m_wrap_s = m_wrap_s; }
        void    set_wrap_t(GLenum m_wrap_t) { m_wrap_t = m_wrap_t; }

    };
}


