#include "VAO.h"
#include <cstdint>

VAO::VAO() {
  glGenVertexArrays(1, &m_ID);
}

void VAO::LinkVBO(VBO& VBO, uint32_t layout, int32_t stride, uintptr_t offset) {
  VBO.Bind();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)(offset*sizeof(float)));
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

void VAO::Bind() {
  glBindVertexArray(m_ID);
}

void VAO::Unbind() {
  glBindVertexArray(0);
}

void VAO::Delete() {
  glDeleteVertexArrays(1, &m_ID);
}
