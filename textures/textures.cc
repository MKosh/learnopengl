#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "../utils/stb_image.h"

#include "../utils/VBO.h"
#include "../utils/VAO.h"
#include "../utils/EBO.h"
#include "../utils/shader.h"
#include "../utils/VBOLayout.h"
#include "../utils/Renderer.h"
#include "../utils/texture.h"

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
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  // glEnable(GL_DEPTH_TEST);
  // Create the shader program
  Shader shader_program("vertex.shader", "fragment.shader");
  
  // Create and bind the Vector array object
  VAO VAO1;
  VAO1.Bind();
  
  // Create VBO and EBO
  VBO VBO1{vertices, sizeof(vertices)};
  EBO EBO1{indices, sizeof(indices)};
  VBOLayout layout; 

  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 2);
  // VAO1.LinkVBO(VBO1, 0, 3, 8, 0);
  // VAO1.LinkVBO(VBO1, 1, 3, 8, 3);
  // VAO1.LinkVBO(VBO1, 2, 2, 8, 6);
  VAO1.LinkVBO(VBO1, layout);

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  Texture texture{"../resources/container.jpg", GL_TEXTURE_2D};
  texture.Bind();
  shader_program.SetUniform1i("u_texture", 0);
  Renderer renderer;

  while(!glfwWindowShouldClose(window)) {
    ProcessInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    // container.TexUnit(shader_program, "tex0", 0);
    // container.Bind();
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // renderer.Clear();
    renderer.Draw(VAO1, EBO1, shader_program);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shader_program.Delete();

  glfwTerminate();
}

auto FramebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int32_t width, int32_t height) -> void
{
  glViewport(0, 0, width, height);
}

auto ProcessInput(GLFWwindow* window) -> void
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
