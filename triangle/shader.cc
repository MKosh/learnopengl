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

void Shader::Use() {
  glUseProgram(m_ID);
}

void Shader::Delete() {
  glDeleteProgram(m_ID);
}

