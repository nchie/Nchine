//
// Created by aejt on 11/11/17.
//

#pragma once

#include <string>

#include <assimp/scene.h>

#include "ResourceCache.h"
#include "Texture2D.h"
#include "Geometry.h"
#include "Mesh.h"
#include "../Scene/SceneNode.h"



namespace Enchine {
    class ModelLoader {

    private:
        ResourceCache<Texture2D> *m_texture_cache;
        ResourceCache<Geometry> *m_geometry_cache;

    public:
        ModelLoader(ResourceCache<Texture2D> *texture_cache, ResourceCache<Geometry> *geometry_cache) : m_texture_cache(texture_cache),
                                                                                                      m_geometry_cache(geometry_cache) { }
        SceneNode load_model(std::string path);
        SceneNode process_node(aiNode* aNode, const aiScene *aScene, std::string directory_path);

        Geometry load_geometry(aiMesh* aMesh, const aiScene* aScene);


    private:


    };
}


