//
// Created by aejt on 10/22/17.
//

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Resources/ResourceCache.h"

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "UniformValue.h"
#include "UniformValueSampler.h"

#include <map>

namespace Enchine {

    class Material {
        Resource<ShaderProgram> m_program;

    private:

        std::map<std::string, UniformValue> m_uniforms; // TODO: Make vector?
        std::map<std::string, UniformValueSampler> m_sampler_uniforms; // TODO: Make vector?
    public:
        Material(const Resource<ShaderProgram>& program);


        void set_bool(std::string name, bool value);
        void set_int(std::string name, int value);
        void set_float(std::string name, float value);
        void set_texture(std::string name, const Resource<Texture2D>&, unsigned int unit);
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
        ShaderProgram           *get_program_ptr() { return &(*m_program); }
        Resource<ShaderProgram>& get_program() { return m_program; }


    };

}
