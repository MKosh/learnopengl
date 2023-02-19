#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <fstream>
#include <iostream>


class Shader {
private:
  uint32_t m_ID;

public:
  Shader(const char* vertex_file, const char* fragment_file);

  uint32_t GetID() {return m_ID;}
  void SetID(uint32_t new_program) {m_ID = new_program;}
  void Use();
  void Delete();
};
