#include "VAO.h"
#include "VBOLayout.h"
#include <cstdint>
#include <iostream>

VAO::VAO() {
  glGenVertexArrays(1, &m_ID);
}

auto VAO::LinkVBO(const VBO &vbo, const VBOLayout &layout) const -> void
{
  vbo.Bind();
  const auto& elements = layout.GetElements();
  uint64_t offset = 0;
  for (uint32_t i = 0; i < elements.size(); ++i) {
    // s_layout_index += i; // use s_layout_index in place of i for the attrib
    // and enable steps?
    const auto& element = elements[i];
    glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
    glEnableVertexAttribArray(i);
    offset += element.count * VBOElement::GetSizeOfType(element.type);
  }
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
