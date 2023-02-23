#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utils/stb_image.h"

#include "../utils/VBO.h"
#include "../utils/VAO.h"
#include "../utils/EBO.h"
#include "../utils/shader.h"

const uint32_t win_height = 600;
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
  // Create the shader program
  Shader shader_program("vertex.shader", "fragment.shader");
  
  // Create an dbind the Vector array object
  VAO VAO1;
  VAO1.Bind();
  
  // Create VBO and EBO
  VBO VBO1{vertices, sizeof(vertices)};
  EBO EBO1{indices, sizeof(indices)};
  
  VAO1.LinkVBO(VBO1, 0, 3, 8, 0);
  VAO1.LinkVBO(VBO1, 1, 3, 8, 3);
  VAO1.LinkVBO(VBO1, 2, 2, 8, 6);

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // Load and create a texture
  //
  int width, height, nr_channels;
  unsigned char* data = stbi_load("../resources/container.jpg", &width, &height,
                                  &nr_channels, 0);
  uint32_t texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "failed to load texture\n";
  }
  stbi_image_free(data);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

  while(!glfwWindowShouldClose(window)) {
    ProcessInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    VAO1.Bind();
    shader_program.Use();

    int model_loc = glGetUniformLocation(shader_program.GetID(), "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
    int view_loc = glGetUniformLocation(shader_program.GetID(), "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
    int proj_loc = glGetUniformLocation(shader_program.GetID(), "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
