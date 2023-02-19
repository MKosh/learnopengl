#include "VAO.h"
#include <cstdint>

VAO::VAO() {
  glGenVertexArrays(1, &m_ID);
}

auto VAO::LinkVBO(VBO& VBO, uint32_t layout, uint32_t num_attribs, int32_t stride, uintptr_t offset) const -> void 
{
  VBO.Bind();
  glVertexAttribPointer(layout, num_attribs, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)(offset*sizeof(float)));
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

auto VAO::Bind() const -> void 
{
  glBindVertexArray(m_ID);
}

auto VAO::Unbind() const -> void 
{
  glBindVertexArray(0);
}

auto VAO::Delete() const -> void 
{
  glDeleteVertexArrays(1, &m_ID);
}
