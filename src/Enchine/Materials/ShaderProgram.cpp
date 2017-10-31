//
// Created by aejt on 10/22/17.
//

#include "ShaderProgram.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Enchine {

    ShaderProgram::ShaderProgram(const std::string &vs_code, const std::string &fs_code) {
        generate(vs_code, fs_code);

    }

    ShaderProgram::ShaderProgram(const std::string &vs_code, const std::string &fs_code, std::initializer_list<std::string> sampler_names)
    {
        generate(vs_code, fs_code);

        use();
        for(const auto& sampler_name : sampler_names)
        {
            add_sampler(sampler_name);
        }
    }

    ShaderProgram::~ShaderProgram()
    {
        // If id is a valid shader id, delete it (if it isn't, it has been moved)
        if(m_id != 0) {
            glDeleteProgram(m_id);
            m_id = 0;
        }
    }

    ShaderProgram::ShaderProgram(ShaderProgram &&other) noexcept{
        this->m_id = other.m_id;
        this->m_sampler_slots = std::move(other.m_sampler_slots);

        // Invalidate old shader's id
        other.m_id = 0;
    }

    ShaderProgram &ShaderProgram::operator=(ShaderProgram &&other) noexcept{
        this->m_id = other.m_id;
        this->m_sampler_slots = std::move(other.m_sampler_slots);

        // Invalidate old shader's id
        other.m_id = 0;

        return *this;
    }

    void ShaderProgram::generate(const std::string &vs_code, const std::string &fs_code) {
        const char *vShaderCode = vs_code.data();
        const char *fShaderCode = fs_code.data();

        unsigned int vertex_handle, fragment_handle;

        // vertex shader
        vertex_handle = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_handle, 1, &vShaderCode, nullptr);
        glCompileShader(vertex_handle);
        check_compile_errors(vertex_handle, "VERTEX");

        // fragment Shader
        fragment_handle = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_handle, 1, &fShaderCode, nullptr);
        glCompileShader(fragment_handle);
        check_compile_errors(fragment_handle, "FRAGMENT");

        // shader program creation
        m_id = glCreateProgram();
        glAttachShader(m_id, vertex_handle);
        glAttachShader(m_id, fragment_handle);
        glLinkProgram(m_id);
        check_compile_errors(m_id, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex_handle);
        glDeleteShader(fragment_handle);
    }


    void ShaderProgram::use() {
        glUseProgram(m_id);
    }

    void ShaderProgram::add_sampler(const std::string& sampler_name) {
        if(m_sampler_slots.size() >= MAX_SAMPLER_SLOTS)
            throw std::exception(); //TODO: Is 16 max slots OK?

        // Set sampler name to slot
        set_int(sampler_name, static_cast<GLuint>(m_sampler_slots.size()));

        // Save sampler name to slot
        m_sampler_slots.push_back(sampler_name);
    }

    void ShaderProgram::add_sampler(std::string&& sampler_name) {
        if(m_sampler_slots.size() >= MAX_SAMPLER_SLOTS)
            throw std::exception(); //TODO: Is 16 max slots OK?

        // Set sampler name to slot
        set_int(sampler_name, static_cast<GLuint>(m_sampler_slots.size()));

        // Save sampler name to slot
        m_sampler_slots.push_back(sampler_name);
    }

    void ShaderProgram::add_samplers(std::initializer_list<std::string> sampler_names) {
        for(const auto& sampler_name : sampler_names)
        {
            add_sampler(sampler_name);
        }
    }

    int ShaderProgram::get_sampler_slot(const std::string &sampler_name) {
        // TODO: Should I do this in a more C++ way or not?

        int slot = -1;
        for(int i = 0; i < m_sampler_slots.size(); i++)
        {
            if(m_sampler_slots[i] == sampler_name){
                slot = i;
                break;
            }
        }
        if(slot >= MAX_SAMPLER_SLOTS)
            throw std::exception(); //TODO: This should be possible?

        return slot;


    }


    void ShaderProgram::set_bool(const std::string &name, bool value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniform1i(loc, value);
    }

    void ShaderProgram::set_int(const std::string &name, int value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniform1i(loc, value);
    }

    void ShaderProgram::set_float(const std::string &name, float value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniform1f(loc, value);
    }

    void ShaderProgram::set_vector(const std::string &name, const glm::vec2 &value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniform2fv(loc, 1, glm::value_ptr(value));
    }

    void ShaderProgram::set_vector(const std::string &name, const glm::vec3 &value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniform3fv(loc, 1, glm::value_ptr(value));
    }

    void ShaderProgram::set_vector(const std::string &name, const glm::vec4 &value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniform4fv(loc, 1, glm::value_ptr(value));
    }


    void ShaderProgram::set_matrix(const std::string &name, const glm::mat2 &value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::set_matrix(const std::string &name, const glm::mat3 &value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
        if (loc >= 0)
            glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::set_matrix(const std::string &name, const glm::mat4 &value) const {
        int loc = glGetUniformLocation(m_id, name.c_str());
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


