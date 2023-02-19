#include "texture.h"
#include <cstdint>
#include "stb_image.h"

Texture::Texture(const char* image, GLenum tex_type, GLenum slot, GLenum format, GLenum pixel_type) {
  m_type = tex_type;
  stbi_set_flip_vertically_on_load(true);
  int32_t width, height, nr_channels;
  unsigned char* bytes = stbi_load(image, &width, &height, &nr_channels, 0);

  glGenTextures(1, &m_ID);
  glActiveTexture(slot);
  glBindTexture(tex_type, m_ID);

  glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(tex_type, 0, format, width, height, 0, format, pixel_type, bytes);
  glGenerateMipmap(tex_type);

  stbi_image_free(bytes);
  glBindTexture(tex_type, 0);
}

auto Texture::TexUnit(Shader shader, const char *uniform, uint32_t unit) const -> void
{
  uint32_t texture_unit = glGetUniformLocation(shader.GetID(), uniform);
  shader.Use();
  glUniform1i(texture_unit, unit);
}

auto Texture::Bind() const -> void
{
  glBindTexture(m_type, m_ID);
}

auto Texture::Unbind() const -> void
{
  glBindTexture(m_type, 0);
}

auto Texture::Delete() const -> void
{
  glDeleteTextures(1, &m_ID);
}
