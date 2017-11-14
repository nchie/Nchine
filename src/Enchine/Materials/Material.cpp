//
// Created by aejt on 10/22/17.
//

#include "Material.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Enchine {
    Material::Material(Resource<ShaderProgram> program) : m_program(std::move(program)){

    }

    void Material::use() {
        m_program->use();
    }

    void Material::set_bool(std::string name, bool value) {
        m_uniforms[name].value = value;
    }

    void Material::set_int(std::string name, int value) {
        m_uniforms[name].value = value;
    }

    void Material::set_float(std::string name, float value) {
        m_uniforms[name].value = value;
    }

    void Material::set_texture(std::string name, const Resource<Texture2D>& value)
    {
        int slot = m_program->get_sampler_slot(name);

        if(slot >= 0)
            m_sampler_uniforms.emplace(name, UniformValueSampler {name, slot, value});
    }

    void Material::set_vector(std::string name, glm::vec2 value) {
        m_uniforms[name].value = value;
    }

    void Material::set_vector(std::string name, glm::vec3 value) {
        m_uniforms[name].value = value;
    }

    void Material::set_vector(std::string name, glm::vec4 value) {
        m_uniforms[name].value = value;
    }

    void Material::set_matrix(std::string name, glm::mat2 value) {
        m_uniforms[name].value = value;
    }

    void Material::set_matrix(std::string name, glm::mat3 value) {
        m_uniforms[name].value = value;
    }

    void Material::set_matrix(std::string name, glm::mat4 value) {
        m_uniforms[name].value = value;
    }

    std::map<std::string, UniformValue> &Material::get_uniforms() {
        return m_uniforms;
    }

    std::map<std::string, UniformValueSampler> &Material::get_sampler_uniforms() {
        return m_sampler_uniforms;
    }
}