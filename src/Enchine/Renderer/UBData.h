//
// Created by aejt on 11/2/17.
//

#pragma once

#include <glm/glm.hpp>

struct UBData
{
    glm::mat4 view_projection;
    glm::mat4 prev_view_projection;
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 inverse_view;
};