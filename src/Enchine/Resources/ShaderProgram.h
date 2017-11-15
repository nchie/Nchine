//
// Created by aejt on 10/22/17.
//

#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <initializer_list>


namespace Enchine {
    class ShaderProgram {
        const int MAX_SAMPLER_SLOTS = 16;
    private:
        unsigned int m_id = 0;
        std::vector< std::string > m_sampler_slots;

    public:
        ShaderProgram(const std::string &vs_code, const std::string &fs_code);
        ShaderProgram(const std::string &vs_code, const std::string &fs_code, std::initializer_list<std::string> sampler_names);
         ~ShaderProgram();

        // Copy constructors: deleted
        ShaderProgram& operator=(const ShaderProgram& other) = delete;
        ShaderProgram(const ShaderProgram& other) = delete;

        // Move constructors
        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;

        void generate(const std::string &vs_code, const std::string &fs_code);

        void use();

        void add_sampler(const std::string& sampler_name);
        void add_sampler(std::string&& sampler_name);
        void add_samplers(std::initializer_list<std::string> sampler_names);
        int get_sampler_slot(const std::string& sampler_name);


        unsigned int get_id() const { return m_id; }

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
