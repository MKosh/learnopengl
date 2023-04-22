#include "shader.h"
#include <cstdint>
#include <sstream>
#include <string>

std::string get_file_contents(const char* file_name) {
  std::ifstream input{file_name};

  if (!input) {
    std::cout << "Error: file " << file_name << " could not be opened!\n";
    std::exit(1);
  }
  std::string line;
  std::stringstream ss;
  
  while(getline(input, line)) {
    ss << line << '\n';
  }
  return ss.str();
}


Shader::Shader(const char* vertex_file, const char* fragment_file) {
  std::string vertex_code = get_file_contents(vertex_file);
  std::string fragment_code = get_file_contents(fragment_file);

  const char* vertex_source = vertex_code.c_str();
  const char* fragment_source = fragment_code.c_str();
  
  uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); 
  
  glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
  glShaderSource(fragment_shader, 1, &fragment_source, nullptr);

  glCompileShader(vertex_shader);
  glCompileShader(fragment_shader);
  
  int success;

  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cout << "ERROR compiling vertex shader!\n";
  }
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cout << "ERROR compiling fragment shader!\n";
  }

  m_ID = glCreateProgram();
  glAttachShader(m_ID, vertex_shader);
  glAttachShader(m_ID, fragment_shader);
  glLinkProgram(m_ID);
  glValidateProgram(m_ID);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

auto Shader::Use() const -> void {
  glUseProgram(m_ID);
}

auto Shader::Delete() const -> void {
  glDeleteProgram(m_ID);
}

auto Shader::SetUniform1i(const std::string &name, int value) -> void {
  glUniform1i(GetUniformLocation(name), value);
}

auto Shader::SetUniform4f(const std::string& name, glm::vec4 values) -> void {
  glUniform4f(GetUniformLocation(name), values.x, values.y, values.z, values.w);
}

auto Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) -> void {
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

auto Shader::SetFloat(const std::string& name, float value) -> void {
  glUniform1f(GetUniformLocation(name), value);
}

auto Shader::SetMat4f(const std::string& name, const glm::mat4& mat) -> void {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

auto Shader::GetUniformLocation(const std::string& name) -> int32_t {
  if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache[name];

  int32_t location = glGetUniformLocation(m_ID, name.c_str());
  if (location == -1)
    std::cout << "Warning: uniform " << name << " doesn't exist!\n";
  
  m_UniformLocationCache[name] = location; 
  return location;

}
