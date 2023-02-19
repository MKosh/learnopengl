#include <cstdint>
#include <iostream>
#include "shader.h"

class Texture {
private:
  uint32_t m_ID;
  GLenum m_type;
public:
  Texture(const char* image, GLenum texture_type, GLenum slot, GLenum format, GLenum pixel_type);

  auto TexUnit(Shader shader, const char* uniform, uint32_t unit) const -> void;
  auto Bind() const -> void;
  auto Unbind() const -> void;
  auto Delete() const -> void;
};
