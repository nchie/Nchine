//
// Created by aejt on 10/24/17.
//

#include "RenderTarget.h"

#include <glad/glad.h>


namespace Enchine {

    RenderTarget::RenderTarget(unsigned int width, unsigned int height, GLenum type, unsigned int color_attachment_count, bool depth_and_stencil) : m_width(width),
                                                                                                                                                    m_height(height),
                                                                                                                                                    m_type(type),
                                                                                                                                                    m_has_depth_and_stencil(depth_and_stencil)
    {
        glGenFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        for (unsigned int i = 0; i < color_attachment_count; ++i)
        {
            // Create texture in-place
            Texture2D *texture = &m_color_attachments.emplace_back();
            texture->set_filter_min(GL_LINEAR);
            texture->set_filter_max(GL_LINEAR);
            texture->set_wrap_s(GL_CLAMP_TO_EDGE);
            texture->set_wrap_t(GL_CLAMP_TO_EDGE);
            texture->set_mipmapping(false);

            GLenum internal_format = GL_RGBA;
            if(type == GL_HALF_FLOAT)
                internal_format = GL_RGBA16F;
            else if (type == GL_FLOAT)
                internal_format = GL_RGBA32F;

            texture->generate(nullptr, width, height, internal_format, GL_RGBA, type);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture->get_id(), 0);
        }

        // then generate Depth/Stencil texture if requested
        if (depth_and_stencil)
        {
            // Create texture in-place
            m_depth_stencil = std::make_unique<Texture2D>();
            m_depth_stencil->set_filter_min(GL_LINEAR);
            m_depth_stencil->set_filter_max(GL_LINEAR);
            m_depth_stencil->set_wrap_s(GL_CLAMP_TO_EDGE);
            m_depth_stencil->set_wrap_t(GL_CLAMP_TO_EDGE);
            m_depth_stencil->set_mipmapping(false);
            m_depth_stencil->generate(nullptr, width, height, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_stencil->get_id(), 0);
        }
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            // TODO: Log and remove exception?
            //Log::Message("Framebuffer not complete!", LOG_ERROR);
            throw std::exception();
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }
}