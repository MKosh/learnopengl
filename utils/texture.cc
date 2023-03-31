#include "texture.h"
#include <cstdint>
#include "stb_image.h"

Texture::Texture(const char* image, GLenum tex_type) {
  m_type = tex_type;
  stbi_set_flip_vertically_on_load(true);
  m_LocalBuffer = stbi_load(image, &m_width, &m_height, &m_BPP, 4);

  glGenTextures(1, &m_ID);
  glBindTexture(tex_type, m_ID);

  glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(tex_type, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
  glGenerateMipmap(tex_type);

  glBindTexture(tex_type, 0);
  
  if(m_LocalBuffer) {
    stbi_image_free(m_LocalBuffer);
  }
}

auto Texture::TexUnit(Shader shader, const char *uniform, uint32_t unit) const -> void
{
  uint32_t texture_unit = glGetUniformLocation(shader.GetID(), uniform);
  shader.Use();
  glUniform1i(texture_unit, unit);
}

auto Texture::Bind(uint32_t slot) const -> void
{
  glActiveTexture(GL_TEXTURE0+slot);
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
