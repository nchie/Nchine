//
// Created by aejt on 10/22/17.
//

#pragma once

#include <glm/glm.hpp>

#include <string>
#include <variant>


namespace Enchine {
    struct UniformValue {
        typedef std::variant<bool, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat2, glm::mat3, glm::mat4> Type;

        Type value;

    };
}