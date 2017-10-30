//
// Created by aejt on 10/30/17.
//

#pragma once

#include <glad/glad.h>

namespace Enchine {

    class ShaderProgram;
    class Texture2D;
    class Mesh;

    class GLContext {

    private:
        GLuint m_active_program = 0;
        GLuint m_active_texture = 0;
        GLuint m_active_vao = 0;

    public:
        void use_program(const ShaderProgram& program);
        void bind_texture(const Texture2D& texture, GLuint unit);
        void draw_mesh(const Mesh& mesh);

    };
}


