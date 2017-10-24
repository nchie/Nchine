//
// Created by aejt on 10/24/17.
//

#pragma once


#include <glad/glad.h>
#include <vector>
#include <memory>


#include "../Materials/Texture2D.h"

namespace Enchine {

    class RenderTarget {
        typedef std::unique_ptr<Texture2D> TexturePtr;

    private:
        unsigned int m_id;
        unsigned int m_width;
        unsigned int m_height;
        GLenum m_type;
        bool m_has_depth_and_stencil;

        std::vector<Texture2D> m_color_attachments;
        TexturePtr m_depth_stencil;

    public:
        RenderTarget(unsigned int width, unsigned int height, GLenum type, unsigned int color_attachment_count, bool depth_and_stencil);
    };

}
