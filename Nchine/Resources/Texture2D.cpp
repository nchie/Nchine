//
// Created by aejt on 10/22/17.
//

#include "Texture2D.h"


#include <exception>

namespace Nchine {

    Texture2D::Texture2D()
    {
        glGenTextures(1, &m_id);
    }

    Texture2D::Texture2D(std::byte* data, int width, int height, GLenum internal_format, GLenum format, GLenum type) : m_width(width)
                                                                                                                     , m_height(height)
                                                                                                                     , m_internal_format(internal_format)
                                                                                                                     , m_format(format)
                                                                                                                     , m_type(type)
    {
        glGenTextures(1, &m_id);
        generate(data, width, height, internal_format, format, type);
    }

    Texture2D::~Texture2D()
    {
        // If id is a valid texture id, delete it (if it isn't, it has been moved)
        if(m_id != 0) {
            glDeleteTextures(1, &m_id);
            m_id = 0;
        }
    }

    Texture2D::Texture2D(Texture2D &&other) noexcept{
        this->m_id              = other.m_id;;
        this->m_width           = other.m_width;
        this->m_height          = other.m_height;
        this->m_internal_format = other.m_internal_format;
        this->m_format          = other.m_format;
        this->m_type            = other.m_type;

        this->m_mipmapping      = other.m_mipmapping;
        this->m_filter_min      = other.m_filter_min;
        this->m_filter_max      = other.m_filter_max;
        this->m_wrap_s          = other.m_wrap_s;
        this->m_wrap_t          = other.m_wrap_t;

        // Invalidate old texture's id
        other.m_id = 0;
    }

    Texture2D &Texture2D::operator=(Texture2D &&other) noexcept{
        this->m_id              = other.m_id;;
        this->m_width           = other.m_width;
        this->m_height          = other.m_height;
        this->m_internal_format = other.m_internal_format;
        this->m_format          = other.m_format;
        this->m_type            = other.m_type;

        this->m_mipmapping      = other.m_mipmapping;
        this->m_filter_min      = other.m_filter_min;
        this->m_filter_max      = other.m_filter_max;
        this->m_wrap_s          = other.m_wrap_s;
        this->m_wrap_t          = other.m_wrap_t;

        // Invalidate old texture's id
        other.m_id = 0;

        return *this;
    }

    void Texture2D::generate(std::byte *data, int width, int height, GLenum internal_format, GLenum format, GLenum type) {
        bind();
        // load image, create texture and generate mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, data);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);    // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_max);

        if(m_mipmapping)
            glGenerateMipmap(GL_TEXTURE_2D);
        unbind();
    }

    void Texture2D::bind(int unit) {
        if (unit >= 0)
            glActiveTexture((unsigned int) GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture2D::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
