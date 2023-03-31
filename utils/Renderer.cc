#include "Renderer.h"
#include <cstdint>

auto Renderer::Clear() const -> void {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Renderer::Draw(const VAO &vao, const EBO &ebo, const Shader &shader) const -> void {
  shader.Use();
  vao.Bind();
  ebo.Bind();
  glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

auto Renderer::Draw(const VAO &vao, uint32_t vertices, const Shader &shader) const -> void {
  shader.Use();
  vao.Bind();
  glDrawArrays(GL_TRIANGLES, 0, vertices);
}
