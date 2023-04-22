#pragma once

#include "shader.h"
#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using u32 = uint32_t;

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coords;
};

struct Texture {
  u32 id;
  std::string type;
};

class Mesh {
private:
  uint32_t m_vao;
  uint32_t m_vbo;
  uint32_t m_ebo;
  std::vector<Vertex> m_vertices;
  std::vector<u32> m_indicies;
  std::vector<Texture> m_textures;
  auto SetupMesh() -> void;

public:
  Mesh(std::vector<Vertex> vertices, std::vector<u32> indicies, std::vector<Texture> textures);
  auto Draw(Shader& shader) -> void;
};
