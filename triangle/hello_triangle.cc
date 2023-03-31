#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>

const uint32_t win_height = 800;
const uint32_t win_width = 800; 

struct ShaderProgramSource {
  std::string vertex_source;
  std::string fragment_source;
  uint32_t vertex_shader = 0;
  uint32_t fragment_shader = 0;
};

[[nodiscard]] ShaderProgramSource ParseShaders(std::string vertex_shader, std::string fragment_shader);
[[nodiscard]] bool CompileShaders(ShaderProgramSource& source);
[[nodiscard]] uint32_t CreateShaderProgram(ShaderProgramSource& source);
void FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height);

int main(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  GLFWwindow* window = glfwCreateWindow(win_width, win_height, "triangle", nullptr, nullptr);
  if(!window){
    std::cout << "failed to init window\n";
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "failed to init GLAD\n";
    return -1;
  }

  glViewport(0, 0, 800, 800); 
  // glEnable(GL_DEPTH_TEST);

  auto shaders = ParseShaders("./vertex.shader", "./fragment.shader");
  if (!CompileShaders(shaders)) {
    std::cout << "ERROR creating the shaders/shader program\n";
    std::exit(1);
  }
  auto program = CreateShaderProgram(shaders);
  
  float vertices[] = {
    -0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
  };

  uint32_t VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  
  float positions2[] = {
    -1.0f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
  };

  uint32_t VBO2, VAO2;
  glGenVertexArrays(1, &VAO2);
  glGenBuffers(1, &VBO2);
  glBindVertexArray(VAO2);

  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions2), positions2, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  float time_value = glfwGetTime();
  float green = 0.0f;
  float blue = 0.0f;
  float red = 0.0f;
  int vertex_color_location = glGetUniformLocation(program, "u_color");
  while (!glfwWindowShouldClose(window)){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    time_value = glfwGetTime();
    green = (std::sin(time_value+(45.0f*M_PI/180.0f))/2.0f) + 0.5f;
    blue = (std::cos(time_value)/2.0f) + 0.5f;
    red = (std::sin(time_value-(45.0f*M_PI/180.0f))/2.0f) + 0.5f;
    glUseProgram(program);

    glUniform4f(vertex_color_location, red, green, blue, 1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) {
  glViewport(0, 0, width, height);
}

[[nodiscard]] ShaderProgramSource ParseShaders(std::string vertex_shader, std::string fragment_shader) {
  std::ifstream vertex_shader_file{vertex_shader};
  std::ifstream fragment_shader_file{fragment_shader};

  if(!vertex_shader_file.is_open() or !fragment_shader_file.is_open()) {
    std::cout << "ERROR: one or both shader files could not be opened\n";
    std::exit(1);
  }
  
  std::string line;
  std::stringstream ss[2];
  while (getline(vertex_shader_file, line)) {
    ss[0] << line << '\n';
  }

  line.clear();

  while (getline(fragment_shader_file, line)) {
    ss[1] << line << '\n';
  }

  return {ss[0].str(), ss[1].str()};
}

[[nodiscard]] bool CompileShaders(ShaderProgramSource& source) {
  int32_t success = 1;

  source.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  source.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); 
  const char* vertex_src = source.vertex_source.c_str();
  const char* fragment_src = source.fragment_source.c_str();

  glShaderSource(source.vertex_shader, 1, &vertex_src, nullptr);
  glShaderSource(source.fragment_shader, 1, &fragment_src, nullptr);

  glCompileShader(source.vertex_shader);
  glCompileShader(source.fragment_shader);

  glGetShaderiv(source.vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cout << "ERROR compiling vertex shader!\n";
  }
  glGetShaderiv(source.fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cout << "ERROR compiling fragment shader!\n";
  }

  return static_cast<bool>(success);
}

[[nodiscard]] uint32_t CreateShaderProgram(ShaderProgramSource& source) {
  uint32_t program = glCreateProgram();
  glAttachShader(program, source.vertex_shader);
  glAttachShader(program, source.fragment_shader);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(source.vertex_shader);
  glDeleteShader(source.fragment_shader);

  return program;
}
