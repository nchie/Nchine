//
// Created by aejt on 10/22/17.
//

#include "Texture2D.h"

#include <glad/glad.h>
#include <exception>

namespace Enchine {

    Texture2D::Texture2D(std::byte *data, int width, int height) {
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load image, create texture and generate mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Texture2D::bind(int unit) {
        if (unit >= 0)
            glActiveTexture((unsigned int) GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
    }
}
