//
// Created by aejt on 10/30/17.
//

#include "GLContext.h"

#include "../Materials/ShaderProgram.h"

void Enchine::GLContext::use_program(const ShaderProgram &program) {
    m_active_program = program.get_id();
    glUseProgram(program.get_id());
}
