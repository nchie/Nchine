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



namespace Nchine {

    class ResourceLibrary;

    class ModelLoader {

    private:
        ResourceLibrary *m_library;
        //ResourceCache<Texture2D> *m_texture_cache;
        //ResourceCache<Geometry> *m_geometry_cache;

    public:
        ModelLoader(ResourceLibrary *resource_library);
        SceneNode load_model(std::string path);
        SceneNode process_node(aiNode* aNode, const aiScene *aScene, const std::string& path);

        Geometry load_geometry(aiMesh* aMesh, const aiScene* aScene);


    private:


    };
}


