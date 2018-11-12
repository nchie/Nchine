//
// Created by aejt on 10/30/17.
//

#pragma once

#include <glad/glad.h>

namespace Nchine {

    class ShaderProgram;
    class Texture2D;
    class Geometry;

    class GLContext {

    private:
        GLuint m_active_program = 0;
        GLuint m_active_texture = 0;
        GLuint m_active_vao = 0;

    public:
        GLContext(GLADloadproc load_proc);

        void use_program(const ShaderProgram& program);
        void bind_texture(unsigned int unit, const Texture2D& texture);
        void draw_mesh(const Geometry& mesh);

    };
}


