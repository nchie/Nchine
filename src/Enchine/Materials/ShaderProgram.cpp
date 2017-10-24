//
// Created by aejt on 10/22/17.
//

#include "ShaderProgram.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Enchine {

    ShaderProgram::ShaderProgram(const std::string &vs_code, const std::string &fs_code) {
        const char *vShaderCode = vs_code.data();
        const char *fShaderCode = fs_code.data();

        unsigned int vertex_handle, fragment_handle;

        // vertex shader
        vertex_handle = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_handle, 1, &vShaderCode, NULL);
        glCompileShader(vertex_handle);
        check_compile_errors(vertex_handle, "VERTEX");

        // fragment Shader
        fragment_handle = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_handle, 1, &fShaderCode, NULL);
        glCompileShader(fragment_handle);
        check_compile_errors(fragment_handle, "FRAGMENT");

        // shader program creation
        m_shader_id = glCreateProgram();
        glAttachShader(m_shader_id, vertex_handle);
        glAttachShader(m_shader_id, fragment_handle);
        glLinkProgram(m_shader_id);
        check_compile_errors(m_shader_id, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex_handle);
        glDeleteShader(fragment_handle);

    }

    ShaderProgram::~ShaderProgram() {
        // TODO: Delete shader program?
    }


    void ShaderProgram::use() {
        glUseProgram(m_shader_id);
    }

    void ShaderProgram::set_bool(const std::string &name, bool value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniform1i(loc, value);
    }

    void ShaderProgram::set_int(const std::string &name, int value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniform1i(loc, value);
    }

    void ShaderProgram::set_float(const std::string &name, float value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniform1f(loc, value);
    }

    void ShaderProgram::set_vector(const std::string &name, const glm::vec2 &value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniform2fv(loc, 1, glm::value_ptr(value));
    }

    void ShaderProgram::set_vector(const std::string &name, const glm::vec3 &value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniform3fv(loc, 1, glm::value_ptr(value));
    }

    void ShaderProgram::set_vector(const std::string &name, const glm::vec4 &value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniform4fv(loc, 1, glm::value_ptr(value));
    }


    void ShaderProgram::set_matrix(const std::string &name, const glm::mat2 &value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::set_matrix(const std::string &name, const glm::mat3 &value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::set_matrix(const std::string &name, const glm::mat4 &value) const {
        int loc = glGetUniformLocation(m_shader_id, name.c_str());
        if (loc >= 0)
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }


    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void ShaderProgram::check_compile_errors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                //std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                //std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

}

