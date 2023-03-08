#include "Resource.h"

#include "Log.h"
#include "stb/stb_image.h"
#include <fstream>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Resource
{
    std::string readFile(const std::string &path)
    {
        std::string text;
        std::ifstream file;

        file.exceptions(std::ifstream::badbit);
        try
        {
            file.open(path);
            std::stringstream sstream;

            sstream << file.rdbuf();

            file.close();
            text = sstream.str();
        }
        catch (std::ifstream::failure e)
        {
            Log::error("could not read file: \"{}\"", path);
        }

        return text;
    }

    Image loadImage(const std::string &path)
    {
        Image image;
        int channels_n;
        image.data = stbi_load(path.c_str(), &image.width, &image.height, &channels_n, 0);
        if (image.data == nullptr)
            Log::error("could not read file: \"{}\"", path);

        image.format = (Format)(channels_n - 1);

        return image;
    }

    void freeImage(Image &image)
    {
        stbi_image_free(image.data);
    }

    Mesh processMesh(aiMesh *mesh);
    void processNode(aiNode *node);

    Assimp::Importer importer;
    const aiScene *scene = nullptr;
    Model model;

    Model loadModel(const std::string &path)
    {
        scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log::error("could not load file: \"{}\"", path);
            return Model();
        }

        processNode(scene->mRootNode);

        scene = nullptr;
        return model;
    }

    void processNode(aiNode *node)
    {
        for (u32 i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            model.meshes.push_back(processMesh(mesh));
        }

        for (u32 i = 0; i < node->mNumChildren; i++)
            processNode(node->mChildren[i]);
    }

    Mesh processMesh(aiMesh *mesh)
    {
        Mesh result;

        for (u32 i = 0; i < mesh->mNumVertices; i++)
        {
            glm::vec3 position;
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;
            result.positions.push_back(position);

            glm::vec3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
            result.normals.push_back(normal);

            glm::vec2 tex_coord;
            tex_coord.x = mesh->mTextureCoords[0]->x;
            tex_coord.y = mesh->mTextureCoords[0]->y;
            result.tex_coords0.push_back(tex_coord);
        }

        for (u32 i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (u32 j = 0; j < face.mNumIndices; j++)
                result.indices.push_back(face.mIndices[j]);
        }

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            aiString texture_path;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path);
            result.texture_path = texture_path.C_Str();
        }

        return result;
    }

    /*  void loadTextures(aiMaterial *material, aiTextureType type)
     {
         for (u32 i = 0; i < material->GetTextureCount(type); i++)
         {
         }
     } */
};