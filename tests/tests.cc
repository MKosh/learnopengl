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

const uint32_t win_height = 800;
const uint32_t win_width = 800;

float vertices[] = {
  // positions        // colors
  0.0f, 0.0f, 0.0f
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

  VAO1.LinkVBO(VBO1, 0, 3, 3, 0);

  VAO1.Unbind();
  VBO1.Unbind();

  while(!glfwWindowShouldClose(window)) {
    ProcessInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    VAO1.Bind();
    shader_program.Use();

    float time = glfwGetTime();
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(std::sin(time), std::cos(time), 0.0f));
    
    // Get transformation uniforms
    uint32_t transform_loc = glGetUniformLocation(shader_program.GetID(), "transform");
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(trans));

    glPointSize(50);
    glDrawArrays(GL_POINTS, 0, 3);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
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
