#pragma once

#include <cstdint>
#include <glad/glad.h>

class EBO {
public:
  uint32_t m_ID;
  EBO(GLuint* indices, GLsizeiptr size);

  void Bind();
  void Unbind();
  void Delete();

};
