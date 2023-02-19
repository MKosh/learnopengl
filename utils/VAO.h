#pragma once

#include <cstdint>
#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
  uint32_t m_ID;

  VAO();
  
  auto LinkVBO(VBO& VBO, uint32_t layout, uint32_t num_attribs, int32_t stride, uintptr_t offset) const -> void;
  auto Bind() const -> void;
  auto Unbind() const -> void;
  auto Delete() const -> void;
};
