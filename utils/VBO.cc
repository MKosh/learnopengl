#include "VBO.h"

VBO::VBO(float* vertices, GLsizeiptr size) {
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
  glDeleteBuffers(1, &m_ID);
}
