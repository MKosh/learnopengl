#pragma once

#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "shader.h"

class Renderer {
public:
  auto Draw(const VAO& vao, const EBO& ebo) const -> void;
};
