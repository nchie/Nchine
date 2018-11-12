//
// Created by aejt on 10/22/17.
//

#pragma once

#include <cstddef>
#include <string>
#include <variant>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Resources/ResourceCache.h"

namespace Nchine {

    class Texture2D;

    struct UniformValue {
        typedef std::variant<bool, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat2, glm::mat3, glm::mat4> Type;
        Type value;
    };

    struct UniformValueSampler
    {
        std::string temp_text;
        unsigned int unit;
        Resource<Texture2D> texture;
    };

    class Texture2D {
    private:
        unsigned int m_id        = 0;
        int m_width              = 0;
        int m_height             = 0;
        GLenum m_internal_format = GL_RGBA;
        GLenum m_format          = GL_RGBA;
        GLenum m_type            = GL_UNSIGNED_BYTE;

        bool m_mipmapping        = true;
        GLenum m_filter_min      = GL_LINEAR_MIPMAP_LINEAR;
        GLenum m_filter_max      = GL_LINEAR;
        GLenum m_wrap_s          = GL_REPEAT;
        GLenum m_wrap_t          = GL_REPEAT;

    public:
        Texture2D();
        Texture2D(std::byte* data, int width, int height, GLenum internal_format, GLenum format, GLenum type);
        ~Texture2D();

        // Copy constructors: deleted
        Texture2D& operator=(const Texture2D& other) = delete;
        Texture2D(const Texture2D& other) = delete;

        // Move constructors
        Texture2D(Texture2D&& other) noexcept;
        Texture2D& operator=(Texture2D&& other) noexcept;

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

        void    set_mipmapping(bool mipmapping) { m_mipmapping = mipmapping; }
        void    set_filter_min(GLenum filter_min) { m_filter_min = filter_min; }
        void    set_filter_max(GLenum filter_max) { m_filter_max = filter_max; }
        void    set_wrap_s(GLenum wrap_s) { m_wrap_s = wrap_s; }
        void    set_wrap_t(GLenum wrap_t) { m_wrap_t = wrap_t; }

    };
}


