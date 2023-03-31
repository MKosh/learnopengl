#include "EBO.h"
#include <cstdint>
#include <iostream>

EBO::EBO(const uint32_t* indices, uint32_t count) : m_count{count}
{
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

// EBO::~EBO()
// {
//   glDeleteBuffers(1, &m_ID);
// }

auto EBO::Bind() const -> void
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

auto EBO::Unbind() const -> void
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto EBO::Delete() const -> void
{
  glDeleteBuffers(1, &m_ID);
}
