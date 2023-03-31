#pragma once

#include <cstdint>
#include <glad/glad.h>

///////////////////////////////////////////////////////////////////////////////
/// Vertex Buffer Object class
class VBO {
public:
  uint32_t m_ID;

  VBO(float* vertices, uint32_t count);
  // ~VBO();
  auto Bind() const -> void;
  auto Unbind() const -> void;
  auto Delete() const -> void;
};
