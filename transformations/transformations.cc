#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utils/VBO.h"
#include "../utils/VAO.h"
#include "../utils/EBO.h"
#include "../utils/shader.h"
#include "../utils/texture.h"
#include "../utils/Renderer.h"
#include "../utils/VBOLayout.h"

const uint32_t win_height = 800;
const uint32_t win_width = 800;

float vertices[] = {
  // positions        // colors         // texture coords
   0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
   0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
  -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // top left
};


GLuint indices[] = {
  0, 1, 3,
  1, 2, 3
};

auto FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) -> void;
auto ProcessInput(GLFWwindow* window) -> void;

int main(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  // glm::mat4 trans{1.0f};
  // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
  // vec = trans * vec;
  // std::cout << vec.x << vec.y << vec.z << std::endl;

  GLFWwindow* window = glfwCreateWindow(win_width, win_height, "Moving texture", nullptr, nullptr);
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
  EBO EBO1{indices, 6};

  VBOLayout layout;
  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 2);

  VAO1.LinkVBO(VBO1, layout);
  // VAO1.LinkVBO(VBO1, 1, 3, 8, 3);
  // VAO1.LinkVBO(VBO1, 2, 2, 8, 6);

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  Texture container{"../resources/container.jpg", GL_TEXTURE_2D};
  container.Bind();


  while(!glfwWindowShouldClose(window)) {
    // Handle input and clear buffers
    ProcessInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up the VAO
    VAO1.Bind();
    shader_program.Use();
    
    // glm math and transformations
    float time = glfwGetTime();
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(std::sin(time), 0.0f, 0.0f));
    // trans = glm::rotate(trans, time, glm::vec3(0.0, 0.0, 1.0));
    // trans = glm::scale(trans, glm::vec3(std::sin(time), std::sin(time), std::sin(time)));
    
    // Get transformation uniforms
    uint32_t transform_loc = glGetUniformLocation(shader_program.GetID(), "transform");
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(trans));
  
    // Get and bind texture unit
    container.TexUnit(shader_program, "tex0", 0);
    container.Bind();

    // Draw call, swap buffers, poll events
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  // VBO1.Delete();
  // EBO1.Delete();
  container.Delete();
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
