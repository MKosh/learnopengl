#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>


class Shader {
private:
  uint32_t m_ID;
  // caching for uniforms
  std::unordered_map<std::string, int32_t> m_UniformLocationCache;
public:
  Shader(const char* vertex_file, const char* fragment_file);

  auto GetID() const -> uint32_t {return m_ID;}
  auto SetID(uint32_t new_program) -> void {m_ID = new_program;}
  auto Use() const -> void;
  auto Delete() const -> void;

  auto SetUniform4f(const std::string& name, glm::vec4 values) -> void;
  auto SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) -> void;
  auto SetVec3f(const std::string& name, float v0, float v1, float v2) -> void;
  auto SetVec3f(const std::string& name, glm::vec3 vec) -> void;
  auto SetMat4f(const std::string& name, const glm::mat4& mat) -> void;
  auto SetFloat(const std::string& name, float value) -> void;
  auto SetUniform1i(const std::string& name, int value) -> void;
private:
  auto GetUniformLocation(const std::string& name) -> int32_t;
};
