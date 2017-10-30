//
// Created by aejt on 10/30/17.
//

#pragma once

#include <glad/glad.h>

namespace Enchine {

    class ShaderProgram;

    class GLContext {

    private:
        GLuint m_active_program = 0;
        GLuint m_active_texture;

    public:
        void use_program(const ShaderProgram& program);

    };
}


