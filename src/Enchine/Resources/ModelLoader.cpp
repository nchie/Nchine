//
// Created by aejt on 11/11/17.
//

#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


namespace Enchine {
    SceneNode ModelLoader::load_model(std::string path) {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            throw std::exception(); // TODO: Assimp failed to load model
        }

        std::string directory = path.substr(0, path.find_last_of('/'));


        return process_node(scene->mRootNode, scene, directory);
    }

    SceneNode ModelLoader::process_node(aiNode* aNode, const aiScene *aScene, std::string directory_path) {
        for (unsigned int i = 0; i < aNode->mNumMeshes; ++i)
        {
            aiMesh*     assimpMesh = aScene->mMeshes[aNode->mMeshes[i]];
            aiMaterial* assimpMat  = aScene->mMaterials[assimpMesh->mMaterialIndex];
            Geometry   geometry   = load_geometry(assimpMesh, aScene);
            //Material   material   = nullptr;
        }


    }


    Geometry ModelLoader::load_geometry(aiMesh* aMesh, const aiScene* aScene) {
        return Geometry(std::vector<float>(), std::vector<int>(), std::bitset<8>());

    }
}

