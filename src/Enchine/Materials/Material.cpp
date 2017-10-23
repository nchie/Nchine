//
// Created by aejt on 10/22/17.
//

#include "Material.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Enchine {
    Material::Material(ShaderProgram *program, Texture2D *texture) : m_program(program),
                                                                     m_texture(texture) {

    }

    void Material::use() {
        m_program->use();
        m_program->set_matrix("transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.0f)));
        m_texture->bind(2);
        m_program->set_int("ourTexture3", 2);
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

    void Material::set_texture(std::string name, Texture2D *value, unsigned int unit) {
        m_uniforms[name].value = value;

        if (m_program)
        {
            m_program->use();
            m_program->set_int(name, unit);
        }
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