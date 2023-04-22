#include "mesh.h"
#include "shader.h"
#include <cstdint>
#include <string>
#include <vector>
#include <glad/glad.h>

using u32 = uint32_t;

Mesh::Mesh(std::vector<Vertex>vertices, std::vector<u32> indicies, std::vector<Texture> textures) :
           m_vertices{vertices}, m_indicies{indicies}, m_textures{textures} {
  SetupMesh();
}

auto Mesh::SetupMesh() -> void {
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(u32), &m_indicies[0], GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  // Vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  // Vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

  glBindVertexArray(0);
}

auto Mesh::Draw(Shader& shader) -> void {
  u32 diffuseNr = 1;
  u32 specularNr = 1;
  for (u32 i = 0; i < m_textures.size(); ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string number;
    std::string name = m_textures[i].type;
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_specular")
      number = std::to_string(specularNr++);

    shader.SetFloat(("material." + name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
  }
  
  glActiveTexture(GL_TEXTURE0);

  // Draw mesh
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
