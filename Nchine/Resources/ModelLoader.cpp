//
// Created by aejt on 11/11/17.
//

#include "ModelLoader.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "ResourceLibrary.h"


#include "TextureLoader.h"



namespace Nchine {
    ModelLoader::ModelLoader(ResourceLibrary *resource_library) : m_library(resource_library) {

    }


    SceneNode ModelLoader::load_model(std::string path) {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes);

        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            throw std::exception(); // TODO: Assimp failed to load model
        }



        return process_node(scene->mRootNode, scene, path);
    }

    SceneNode ModelLoader::process_node(aiNode* aNode, const aiScene *aScene, const std::string& path) {

        std::string directory = path.substr(0, path.find_last_of('/')+1);
        std::string file_name = path.substr(path.find_last_of('/')+1, path.length());

        SceneNode node;
        for (unsigned int i = 0; i < aNode->mNumMeshes; ++i)
        {
            aiMesh*     assimpMesh = aScene->mMeshes[aNode->mMeshes[i]];
            aiMaterial* assimpMat  = aScene->mMaterials[assimpMesh->mMaterialIndex];
            Geometry   geometry   = load_geometry(assimpMesh, aScene);

            //assimpMesh->mMaterialIndex

            Material mat1 = m_library->get_shader("DeferredGeometryShader");
            Resource<Geometry> r_geometry = m_library->store_geometry(path + std::to_string(i), std::move(geometry));

            aiMaterial *aMaterial = aScene->mMaterials[assimpMesh->mMaterialIndex];


            unsigned char *data;
            int width, height, nr_channels;
            GLenum format;

            aiString file;

            aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
            std::string dif_texture_name = std::string(file.C_Str());

            aMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
            std::string spec_texture_name = std::string(file.C_Str());


            TextureLoader loader;

            auto diffuse = m_library->store_texture(directory + dif_texture_name);
            auto specular = m_library->store_texture(directory + spec_texture_name);

            mat1.set_texture("texture_diffuse1", diffuse);
            mat1.set_texture("texture_specular1", specular);

            node.add_mesh(Mesh(r_geometry, mat1));
        }

        // also recursively parse this node's children
        for (unsigned int i = 0; i < aNode->mNumChildren; ++i)
        {
            //node->AddChild(process_node(aNode->mChildren[i], aScene, directory_path));
        }

        return node;
    }



    Geometry ModelLoader::load_geometry(aiMesh* aMesh, const aiScene* aScene) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;
        std::vector<unsigned int> indices;

        positions.resize(aMesh->mNumVertices);
        normals.resize(aMesh->mNumVertices);

        if (aMesh->mNumUVComponents > 0)
        {
            uv.resize(aMesh->mNumVertices);
            tangents.resize(aMesh->mNumVertices);
            bitangents.resize(aMesh->mNumVertices);
        }

        indices.resize(aMesh->mNumFaces * 3);

        glm::vec3 pMin( 99999.0f);
        glm::vec3 pMax(-99999.0f);

        for (unsigned int i = 0; i < aMesh->mNumVertices; ++i)
        {
            positions[i] = glm::vec3(aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z);
            normals[i] = glm::vec3(aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z);
            if (aMesh->mTextureCoords[0])
            {
                uv[i] = glm::vec2(aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y);

            }
            if (aMesh->mTangents)
            {
                tangents[i] = glm::vec3(aMesh->mTangents[i].x, aMesh->mTangents[i].y, aMesh->mTangents[i].z);
                bitangents[i] = glm::vec3(aMesh->mBitangents[i].x, aMesh->mBitangents[i].y, aMesh->mBitangents[i].z);
            }
            if (positions[i].x < pMin.x) pMin.x = positions[i].x;
            if (positions[i].y < pMin.y) pMin.y = positions[i].y;
            if (positions[i].z < pMin.z) pMin.z = positions[i].z;
            if (positions[i].x > pMax.x) pMax.x = positions[i].x;
            if (positions[i].y > pMax.y) pMax.y = positions[i].y;
            if (positions[i].z > pMax.z) pMax.z = positions[i].z;
        }
        for (unsigned int f = 0; f < aMesh->mNumFaces; ++f)
        {
            // we know we're always working with triangles due to TRIANGULATE option.
            for (unsigned int i = 0; i < 3; ++i)
            {
                indices[f * 3 + i] = aMesh->mFaces[f].mIndices[i];
            }
        }


        //Geometry test(positions, uv, normals, indices);

        return Geometry(positions, uv, normals, indices);

    }
}

