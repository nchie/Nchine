//
// Created by aejt on 10/23/17.
//

#include <glm/glm.hpp>


namespace Nchine
{
    class Geometry;
    class Material;

    struct RenderCommand
    {
        glm::mat4  transform;
        glm::mat4  prev_transform;
        Geometry*      mesh;
        Material*  material;
        glm::vec3  box_min; //TODO: ?
        glm::vec3  box_max; //TODO: ?
    };

}