//
// Created by aejt on 10/24/17.
//

#include "RenderTarget.h"

#include <glad/glad.h>


namespace Enchine {

    RenderTarget::RenderTarget(unsigned int width, unsigned int height) : m_width(width),
                                                                          m_height(height)
    {
        // TODO: Default render target doesn't require any settings here?
    }

    RenderTarget::RenderTarget(unsigned int width, unsigned int height, bool depth_and_stencil, std::initializer_list< std::pair<GLenum, GLenum> > attachments) : m_width(width),
                                                                                                                                                              m_height(height),
                                                                                                                                                              m_has_depth_and_stencil(depth_and_stencil)
    {
        glGenFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        std::vector<unsigned int> attachment_enums;

        for(auto& attachment : attachments)
        {
            // Create texture in-place
            Texture2D *texture = &m_color_attachments.emplace_back();
            texture->set_filter_min(GL_LINEAR);
            texture->set_filter_max(GL_LINEAR);
            texture->set_wrap_s(GL_CLAMP_TO_EDGE);
            texture->set_wrap_t(GL_CLAMP_TO_EDGE);
            texture->set_mipmapping(false);

            GLenum internal_format = GL_RGBA;
            if(attachment.second == GL_UNSIGNED_BYTE)
                internal_format = GL_RGB8;
            else if(attachment.second == GL_HALF_FLOAT)
                internal_format = GL_RGBA16F;
            else if (attachment.second == GL_FLOAT)
                internal_format = GL_RGBA32F;

            attachment_enums.push_back(attachment.first);


            texture->generate(nullptr, width, height, internal_format, GL_RGBA, attachment.second);
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment.first, GL_TEXTURE_2D, texture->get_id(), 0);
        }

        // State how many color attachments this buffer uses
        glDrawBuffers(static_cast<GLsizei>(attachment_enums.size()), attachment_enums.data());

        // then generate Depth/Stencil texture if requested
        if (depth_and_stencil)
        {
            // Create texture in-place
            m_depth_stencil = Texture2D();
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


    RenderTarget::RenderTarget(unsigned int width, unsigned int height, GLenum type, unsigned int color_attachment_count, bool depth_and_stencil) : m_width(width),
                                                                                                                                                    m_height(height),
                                                                                                                                                    m_type(type),
                                                                                                                                                    m_has_depth_and_stencil(depth_and_stencil)
    {
        glGenFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        std::vector<unsigned int> attachment_enums;

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

            attachment_enums.push_back(GL_COLOR_ATTACHMENT0 + i);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture->get_id(), 0);
        }

        // State how many color attachments this buffer uses
        glDrawBuffers(static_cast<GLsizei>(attachment_enums.size()), attachment_enums.data());

        // then generate Depth/Stencil texture if requested
        if (depth_and_stencil)
        {
            // Create texture in-place
            m_depth_stencil = Texture2D();
            m_depth_stencil->set_filter_min(GL_LINEAR);
            m_depth_stencil->set_filter_max(GL_LINEAR);
            m_depth_stencil->set_wrap_s(GL_CLAMP_TO_EDGE);
            m_depth_stencil->set_wrap_t(GL_CLAMP_TO_EDGE);
            m_depth_stencil->set_mipmapping(false);
            m_depth_stencil->generate(nullptr, width, height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);

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

    RenderTarget::~RenderTarget() {
        if(m_id > 0) // TODO: 0 is the default FB which we don't want to delete?
        {
            glDeleteFramebuffers(1, &m_id);
        }
    }

    RenderTarget::RenderTarget(RenderTarget &&other) noexcept {
        // TODO: Check for self assignment

        this->m_id   = other.m_id;
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        this->m_type = other.m_type;
        this->m_has_depth_and_stencil = other.m_has_depth_and_stencil;

        this->m_color_attachments = std::move(other.m_color_attachments);
        this->m_depth_stencil = std::move(other.m_depth_stencil);

        // Invalidate old mesh's ids
        other.m_id = 0;
    }

    RenderTarget &RenderTarget::operator=(RenderTarget &&other) noexcept {
        // TODO: Check for self assignment

        this->m_id   = other.m_id;
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        this->m_type = other.m_type;
        this->m_has_depth_and_stencil = other.m_has_depth_and_stencil;

        this->m_color_attachments = std::move(other.m_color_attachments);
        this->m_depth_stencil = std::move(other.m_depth_stencil);

        // Invalidate old mesh's ids
        other.m_id = 0;

        return *this;
    }
}