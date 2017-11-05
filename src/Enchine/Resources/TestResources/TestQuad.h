//
// Created by aejt on 11/3/17.
//

#pragma once

#include <glm/glm.hpp>
#include <vector>

static const std::vector<glm::vec3> quad_positions{
        {-1.0f,  1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f},
        { 1.0f,  1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f}
};





static const std::vector<glm::vec2> quad_texcoords {
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f}
};


static const std::vector<int> quad_indices {
        0, 1, 2,
        1, 2, 3
};