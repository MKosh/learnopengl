#include "model.h"
#include "mesh.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>
#include <glm/fwd.hpp>
#include <iostream>

auto TextureFromFile(const char* path, const std::string& directory) -> u32;

Model::Model(const std::string& path) { Model::LoadModel(path); }

auto Model::Draw(Shader shader) -> void {
  // for (u32 i = 0; i < m_meshes.size(); ++i) {
  //   m_meshes[i].Draw(shader);
  // }
  for (auto &mesh : m_meshes) {
    mesh.Draw(shader);
  }
}

auto Model::LoadModel(const std::string& path) -> void {
  Assimp::Importer import;
  const aiScene *scene =
      import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cout << "ERROR: ASSIMP: " << import.GetErrorString() << '\n';
    return;
  }

  m_directory = path.substr(0, path.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}

auto Model::ProcessNode(aiNode *node, const aiScene *scene) -> void {
  for (u32 i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_meshes.push_back(ProcessMesh(mesh, scene));
  }

  for (u32 i = 0; i < node->mNumChildren; ++i) {
    ProcessNode(node->mChildren[i], scene);
  }
}

auto Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) -> Mesh {
  std::vector<Vertex> vertices;
  std::vector<u32> indicies;
  std::vector<Texture> textures;

  for (u32 i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;
    glm::vec3 vector{mesh->mVertices[i].x, mesh->mVertices[i].y,
                     mesh->mVertices[i].z};
    vertex.position = vector;
    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;
    }
    
    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.tex_coords = vec;

      // vector.x = mesh->mTangents[i].x;
      // vector.y = mesh->mTangents[i].y;
      // vector.z = mesh->mTangents[i].z;
      // vertex.tangent = vector;

      // vector.x = mesh->mBitangents[i].x;
      // vector.y = mesh->mBitangents[i].y;
      // vector.z = mesh->mBitangents[i].z;
      // vertex.bitangent = vector;
    } else {
      vertex.tex_coords = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  for (u32 i = 0; i < mesh->mNumFaces; ++i) {
    aiFace face = mesh->mFaces[i];
    for (u32 j = 0; j < face.mNumIndices; ++j) {
      indicies.push_back(face.mIndices[j]);
    }
  }

  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

  std::vector<Texture> diffuse_maps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
    
  std::vector<Texture> specular_maps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

  std::vector<Texture> normal_maps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
  textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
  
  std::vector<Texture> height_maps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
  textures.insert(textures.end(), height_maps.begin(), height_maps.end());
  

  return Mesh(vertices, indicies, textures);
}

auto Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name) -> std::vector<Texture> {
  std::vector<Texture> textures;
  for (u32 i = 0; i < mat->GetTextureCount(type); ++i) {
    aiString str;
    mat->GetTexture(type, i, &str);
    bool skip = false;
    for (u32 j = 0; j < m_textures_loaded.size(); ++j) {
      if (std::strcmp(m_textures_loaded[j].path.data(), str.C_Str()) == 0) {
        textures.push_back(m_textures_loaded[j]);
        skip = true;
        break;
      }
    }
    if (!skip) {
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), m_directory);
      texture.type = type_name;
      texture.path = str.C_Str();
      textures.push_back(texture);
      m_textures_loaded.push_back(texture);
    }
  }
  return textures;
}

auto TextureFromFile(const char* path, const std::string& directory) -> u32 {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  u32 textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  std::cout << filename << '\n';
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1) {
      format = GL_RED;
    } else if (nrComponents == 3) {
      format = GL_RGB;
    } else if (nrComponents == 4) {
      format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}
