#pragma once

#include <cstdint>
#include <iostream>
#include "shader.h"

class Texture {
private:
  uint32_t m_ID;
  GLenum m_type;
  int32_t m_width;
  int32_t m_height;
  int32_t m_BPP; // Bits per pixel
  unsigned char* m_LocalBuffer;
public:
  Texture(const char* image, GLenum texture_type);

  auto TexUnit(Shader shader, const char* uniform, uint32_t unit) const -> void;
  auto Bind(uint32_t slot = 0) const -> void;
  auto Unbind() const -> void;
  auto Delete() const -> void;

  inline auto GetWidth() const -> int32_t { return m_width; }
  inline auto GetHeight() const -> int32_t { return m_height; }
};
