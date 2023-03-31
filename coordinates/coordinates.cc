#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

#include "../utils/stb_image.h"

#include "../utils/VBO.h"
#include "../utils/VAO.h"
#include "../utils/EBO.h"
#include "../utils/shader.h"
#include "../utils/VBOLayout.h"
#include "../utils/texture.h"
#include "../utils/Renderer.h"

const uint32_t win_height = 800;
const uint32_t win_width = 800;

float vertices[] = {
  // positions        // colors         // texture coords
 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f 
};

// float vertices[] = {
//   // positions         // texture coords
//    0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
//    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
//   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
//   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
// };


// GLuint indices[] = {
//   0, 1, 3,
//   1, 2, 3
// };

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
    glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LESS);
  // Create the shader program
  Shader shader_program("vertex.shader", "fragment.shader");
  
  // Create an dbind the Vector array object
  VAO VAO1;
  VAO1.Bind();
  
  // Create VBO and EBO
  std::cout << "count = " << sizeof(vertices)/sizeof(float) << '\n';
  VBO VBO1{vertices, sizeof(vertices)/sizeof(float)};
  // EBO ebo1{indices, 6};
  VBOLayout layout;
  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 2);
  VAO1.LinkVBO(VBO1, layout);
  // VAO1.LinkVBO(VBO1, 1, 2, 5, 3);

  VAO1.Unbind();
  VBO1.Unbind();
  // ebo1.Unbind();
  Texture texture{"../resources/container.jpg", GL_TEXTURE_2D};
  texture.Bind();
  shader_program.SetUniform1i("u_texture", 0);
  
  Renderer renderer;

  while(!glfwWindowShouldClose(window)) {
    ProcessInput(window);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader_program.Use();
    VAO1.Bind();
    renderer.Clear();     

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime()/*glm::radians(50.0f)*/, glm::vec3(0.5f, 1.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f/800.0f, 0.001f, 1000.0f);

    int model_loc = glGetUniformLocation(shader_program.GetID(), "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
    int view_loc = glGetUniformLocation(shader_program.GetID(), "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
    int proj_loc = glGetUniformLocation(shader_program.GetID(), "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

    // renderer.Draw(VAO1, 36, shader_program);
    // renderer.Draw(VAO1, ebo1, shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  // ebo1.Delete();
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
