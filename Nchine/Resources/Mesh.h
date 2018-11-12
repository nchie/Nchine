//
// Created by aejt on 11/14/17.
//

#pragma once

#include "ResourceCache.h"
#include "Geometry.h"
#include "Material.h"

namespace Nchine {

    class Mesh {

    private:
        Resource<Geometry> m_geometry;
        Material m_material;

    public:
        Mesh(Resource<Geometry> geometry, Material material) : m_geometry(std::move(geometry)),
                                                               m_material(std::move(material))  { }

        Geometry& get_geometry() { return *m_geometry; }
        Material& get_material() { return m_material; }

    };
}

