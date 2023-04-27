#include "mesh.h"
#include "shader.h"
#include <filesystem>
#include <string_view>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
  Model(const std::string& path);
  auto Draw(Shader shader) -> void;

private:
  std::vector<Mesh> m_meshes;
  std::string m_directory;
  std::vector<Texture> m_textures_loaded;
  // std::filesystem::path m_directory;

  auto LoadModel(const std::string& path) -> void;
  auto ProcessNode(aiNode* node, const aiScene* scene) -> void;
  auto ProcessMesh(aiMesh* mesh, const aiScene* scene) -> Mesh; 
  auto LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name) -> std::vector<Texture>;
};
