#pragma once

#include <cstdint>
#include <glad/glad.h>
#include "VBO.h"
#include "VBOLayout.h"

class VAO {
private:
  uint32_t m_ID;
public:
  // If I'm understanding things correctly, 
  // A static variable might be useful here when using the same VAO multiple
  // times. Without it when you go to link the next VBO the buffers with index's
  // 0, 1, etc. will be overwritten by the new buffers instead of added on as
  // new buffers.
  //
  // static inline uint32_t s_layout_index{0};
  VAO();
  
  ////////////////////////////////////////////////////////////////////////////
  /// Link a VBO to the this VAO
  /// Params: VBO, layout, number of attributes, stride between vertices, offset
  auto LinkVBO(const VBO& vbo, const VBOLayout& layout) const -> void;
  auto Bind() const -> void;
  auto Unbind() const -> void;
  auto Delete() const -> void;
};
