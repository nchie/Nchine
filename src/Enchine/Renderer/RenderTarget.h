//
// Created by aejt on 10/24/17.
//

#pragma once


#include <glad/glad.h>
#include <vector>
#include <memory>
#include <optional>


#include "../Materials/Texture2D.h"

namespace Enchine {

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
        RenderTarget();
        RenderTarget(unsigned int width, unsigned int height, GLenum type, unsigned int color_attachment_count, bool depth_and_stencil);
        ~RenderTarget();

        // Copy constructors: deleted
        RenderTarget& operator=(const RenderTarget& other) = delete;
        RenderTarget(const RenderTarget& other) = delete;

        // Move constructors
        RenderTarget(RenderTarget&& other) noexcept;
        RenderTarget& operator=(RenderTarget&& other) noexcept;

        unsigned int get_id() const { return m_id; }
    };

}
