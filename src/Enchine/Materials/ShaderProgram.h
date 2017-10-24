//
// Created by aejt on 10/22/17.
//

#pragma once

#include <string>

#include <glm/glm.hpp>


namespace Enchine {
    class ShaderProgram {
    private:
        unsigned int m_shader_id;
    public:
        ShaderProgram(const std::string &vs_code, const std::string &fs_code);

        virtual ~ShaderProgram();

        void use();

        void set_bool(const std::string &name, bool value) const;

        void set_int(const std::string &name, int value) const;

        void set_float(const std::string &name, float value) const;

        void set_vector(const std::string &name, const glm::vec2 &value) const;

        void set_vector(const std::string &name, const glm::vec3 &value) const;

        void set_vector(const std::string &name, const glm::vec4 &value) const;

        void set_matrix(const std::string &name, const glm::mat2 &value) const;

        void set_matrix(const std::string &name, const glm::mat3 &value) const;

        void set_matrix(const std::string &name, const glm::mat4 &value) const;


    private:
        void check_compile_errors(unsigned int shader, std::string type);

    };


}