#pragma once

#include "VAO.h"
#include "EBO.h"
// #include "VBO.h"
#include "shader.h"
#include <cstdint>

class Renderer {
private:

public:
  // Renderer();
  auto Clear() const -> void;
  auto Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const -> void;
  auto Draw(const VAO& vao, uint32_t vertices, const Shader& shader) const -> void;
};
