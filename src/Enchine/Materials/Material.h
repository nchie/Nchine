//
// Created by aejt on 10/22/17.
//

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "UniformValue.h"
#include "UniformValueSampler.h"

#include <map>

namespace Enchine {

    class Material {
        ShaderProgram *m_program;

    private:

        std::map<std::string, UniformValue> m_uniforms;
        std::map<std::string, UniformValueSampler> m_sampler_uniforms;
    public:
        Material(ShaderProgram *program);


        void set_bool(std::string name, bool value);
        void set_int(std::string name, int value);
        void set_float(std::string name, float value);
        void set_texture(std::string name, Texture2D *value, unsigned int unit);
        void set_vector(std::string name, glm::vec2 value);
        void set_vector(std::string name, glm::vec3 value);
        void set_vector(std::string name, glm::vec4 value);
        void set_matrix(std::string name, glm::mat2 value);
        void set_matrix(std::string name, glm::mat3 value);
        void set_matrix(std::string name, glm::mat4 value);

        std::map<std::string, UniformValue>&        get_uniforms();
        std::map<std::string, UniformValueSampler>& get_sampler_uniforms();

        void use(); // TODO: Remove?

    public: // Getters and setters
        ShaderProgram *get_program() const { return m_program; }


    };

}
