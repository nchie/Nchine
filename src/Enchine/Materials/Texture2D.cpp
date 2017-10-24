//
// Created by aejt on 10/22/17.
//

#include "Texture2D.h"


#include <exception>

namespace Enchine {

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

    void Texture2D::generate(std::byte *data, int width, int height, GLenum internal_format, GLenum format, GLenum type) {
        bind();
        // load image, create texture and generate mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, m_type, data);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
