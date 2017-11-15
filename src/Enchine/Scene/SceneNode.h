//
// Created by aejt on 10/23/17.
//

#pragma once

#include <glm/glm.hpp>

#include "../Resources/Mesh.h"

namespace Enchine {

    class SceneGraph;

    class SceneNode {
    private:
        std::vector<Mesh> m_meshes;

        // Transforms
        glm::mat4 m_transform;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale = glm::vec3(1.0f);

        // Bounding box
        glm::vec3 m_min_box = glm::vec3(-99999.0f);
        glm::vec3 m_max_box = glm::vec3( 99999.0f);


    public:
        //SceneNode();

        //Material& get_materials() const { return m_mesh.get_material(); }
        //Geometry& get_geometrys() const { return m_mesh.get_geometry(); }

        std::vector<Mesh>& get_meshes() { return m_meshes; }
        void add_mesh(Mesh mesh) { m_meshes.push_back(mesh); }

        glm::mat4 get_transform() const { return m_transform; }

        void set_transform(glm::mat4 transform) { m_transform = transform; }




    };

}

