#include "VBO.h"

VBO::VBO(float* vertices, GLsizeiptr size) {
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// VBO::~VBO()
// {
//   glDeleteBuffers(1, &m_ID);  
// }

auto VBO::Bind() const -> void
{
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

auto VBO::Unbind() const -> void
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto VBO::Delete() const -> void
{
  glDeleteBuffers(1, &m_ID);
}

