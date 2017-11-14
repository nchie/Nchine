//
// Created by aejt on 10/23/17.
//

#pragma once

#include <glm/glm.hpp>

#include "../Resources/ResourceCache.h"
#include "../Meshes/Mesh.h"
#include "../Materials/Material.h"

namespace Enchine {

    class SceneGraph;

    class SceneNode {
    private:
        Material m_material;
        Resource<Mesh> m_mesh;

        // Transforms
        glm::mat4 m_transform;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale = glm::vec3(1.0f);

        // Bounding box
        glm::vec3 m_min_box = glm::vec3(-99999.0f);
        glm::vec3 m_max_box = glm::vec3( 99999.0f);


    public:
        SceneNode(Material material, Resource<Mesh> mesh);

        Material& get_material() { return m_material; }
        Mesh& get_mesh() { return *m_mesh; }
        glm::mat4 get_transform() const { return m_transform; }

        void set_transform(glm::mat4 transform) { m_transform = transform; }




    };

}

