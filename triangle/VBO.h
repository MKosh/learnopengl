#pragma once

#include <glad/glad.h>

class VBO {
public:
  uint32_t m_ID;

  VBO(float* vertices, GLsizeiptr size);

  void Bind();
  void Unbind();
  void Delete();
};
