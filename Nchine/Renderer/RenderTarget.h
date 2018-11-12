//
// Created by aejt on 10/24/17.
//

#pragma once


#include <glad/glad.h>
#include <vector>
#include <memory>
#include <optional>


#include "../Resources/Texture2D.h"

namespace Nchine {

    class RenderTarget {

    private:
        unsigned int m_id = 0;
        unsigned int m_width;
        unsigned int m_height;
        GLenum m_type;
        bool m_has_depth_and_stencil;

        std::vector<Texture2D> m_color_attachments;
        std::optional<Texture2D> m_depth_stencil;

    public:
        RenderTarget(unsigned int width, unsigned int height);
        RenderTarget(unsigned int width, unsigned int height, bool depth_and_stencil, std::initializer_list< std::pair<GLenum, GLenum> > attachments);
        RenderTarget(unsigned int width, unsigned int height, GLenum type, unsigned int color_attachment_count, bool depth_and_stencil);
        ~RenderTarget();

        // Copy constructors: deleted
        RenderTarget& operator=(const RenderTarget& other) = delete;
        RenderTarget(const RenderTarget& other) = delete;

        // Move constructors
        RenderTarget(RenderTarget&& other) noexcept;
        RenderTarget& operator=(RenderTarget&& other) noexcept;

        unsigned int get_id() const { return m_id; }
        unsigned int get_width() const { return m_width; }
        unsigned int get_height() const { return m_height; }
        Texture2D& get_color_texture(unsigned int index){ return m_color_attachments[index]; };
        Texture2D& get_depth_stencil_texture(){ return *m_depth_stencil; };
    };

}
