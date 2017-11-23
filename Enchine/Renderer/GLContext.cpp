//
// Created by aejt on 10/30/17.
//

#include "GLContext.h"

#include "../Resources/ShaderProgram.h"
#include "../Resources/Texture2D.h"
#include "../Resources/Geometry.h"

namespace Enchine {

    GLContext::GLContext(GLADloadproc load_proc) {
        if (!gladLoadGLLoader(load_proc))
        {
            throw std::exception();  //Failed to initialize GLAD
        }
    }

    void GLContext::use_program(const ShaderProgram &program) {
        if (m_active_program != program.get_id()) {
            glUseProgram(program.get_id());
            m_active_program = program.get_id();
        }
    }

    void GLContext::bind_texture(unsigned int unit, const Texture2D &texture) {
        if (unit >= 0) {
            glActiveTexture((unsigned int) GL_TEXTURE0 + unit);
            m_active_texture = unit;
        }
        glBindTexture(GL_TEXTURE_2D, texture.get_id());
    }

    void GLContext::draw_mesh(const Enchine::Geometry &mesh) {
        if (m_active_vao != mesh.get_vao()) {
            glBindVertexArray(mesh.get_vao());
        }
        glDrawElements(GL_TRIANGLES, mesh.get_indice_count(), GL_UNSIGNED_INT, nullptr);
    }

}