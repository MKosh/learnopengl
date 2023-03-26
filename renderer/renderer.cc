#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utils/VBO.h"
#include "../utils/VAO.h"
#include "../utils/EBO.h"
#include "../utils/shader.h"
#include "../utils/VBOLayout.h"

const uint32_t win_height = 800;
const uint32_t win_width = 800;

float vertices[] = {
  // positions        // colors
   0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
   0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
};

// float vertices[] = {
//   // positions        // colors
//    0.5f, -0.5f, 0.0f,
//   -0.5f, -0.5f, 0.0f,
//    0.0f,  0.5f, 0.0f,
// };


GLuint indices[] = {
  0, 1, 2 
};

auto FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) -> void;
auto ProcessInput(GLFWwindow* window) -> void;

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

  Shader shader_program("vertex.shader", "fragment.shader");

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1{vertices, sizeof(vertices)};
  EBO EBO1{indices, sizeof(indices)};

  VBOLayout layout;
  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 3);

  // VAO1.LinkVBO(VBO1, 0, 3, 6, 0);
  // VAO1.LinkVBO(VBO1, 1, 3, 6, 3);
  VAO1.LinkVBO(VBO1, layout);

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  while(!glfwWindowShouldClose(window)) {
    ProcessInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    VAO1.Bind();
    shader_program.Use();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shader_program.Delete();

  glfwTerminate();
}

auto FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) -> void
{
  glViewport(0, 0, width, height);
}

auto ProcessInput(GLFWwindow* window) -> void
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}