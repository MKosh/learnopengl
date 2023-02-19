#pragma once

#include <cstdint>
#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
  uint32_t m_ID;

  VAO();
  
  void LinkVBO(VBO& VBO, uint32_t layout, int32_t stride, uintptr_t offset);
  void Bind();
  void Unbind();
  void Delete();
};
