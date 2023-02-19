#pragma once

#include <glad/glad.h>

class VBO {
public:
  uint32_t m_ID;

  VBO(float* vertices, GLsizeiptr size);

  auto Bind() const -> void;
  auto Unbind() const -> void;
  auto Delete() const -> void;
};
