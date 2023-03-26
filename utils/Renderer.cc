#include "Renderer.h"

auto Renderer::Clear() const -> void {
  glClear(GL_COLOR_BUFFER_BIT);
}

auto Renderer::Draw(const VAO &vao, const EBO &ebo, const Shader &shader) const -> void {
  shader.Use();
  vao.Bind();
  ebo.Bind();
  glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
}
