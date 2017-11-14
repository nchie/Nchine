//
// Created by aejt on 10/23/17.
//

#include "SceneNode.h"


namespace Enchine
{
    SceneNode::SceneNode(Material material, Resource<Mesh> mesh) : m_material(material),
                                                                   m_mesh(std::move(mesh))
    {

    }

}