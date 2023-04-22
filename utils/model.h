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
  Model(std::string_view path);
  auto Draw(Shader shader) -> void;

private:
  std::vector<Mesh> m_meshes;
  // std::string m_directory;
  std::filesystem::path m_directory;

  auto LoadModel(std::filesystem::path path) -> void;
  auto ProcessNode(aiNode* node, const aiScene* scene) -> void;
  auto ProcessMesh(aiMesh* mesh, const aiScene* scene) -> Mesh; 
  auto LoadMadterial(aiMaterial* mat, aiTextureType type, std::string type_name) -> std::vector<Texture>;
};
