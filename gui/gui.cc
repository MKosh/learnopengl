#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

#include "../utils/imgui.h"
#include "../utils/imgui_impl_glfw.h"
#include "../utils/imgui_impl_opengl3.h"

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
  // positions        // texture coords
 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
  0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
  0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
  0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
 -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
 -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
 -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f 
};

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f) 
};

bool first_mouse = true;
glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
float dt = 0.0f;
float last_frame = 0.0f;
float yaw = -90.0f;
float pitch = 0.0f;
float last_x = win_width/2.0, last_y = win_height/2.0;

glm::vec3 direction{cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
                    sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch))};

glm::vec3 camera_front = glm::normalize(direction);

auto FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) -> void;
auto ProcessInput(GLFWwindow* window) -> void;
auto mouse_callback(GLFWwindow* window, double xpos, double ypos) -> void;

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
  glfwSetCursorPosCallback(window, mouse_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "failed to init GLAD\n";
    return -1;
  }

  glViewport(0, 0, 800, 800); 
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Enable depth test: NOTE for whatever reason this doesn't seem to work on my
  // laptop under wsl. Seems to work okay on my desktop though. I'm guessing it's
  // a graphics driver thing or something. It just produces a blank screen.
  // Updated graphics drivers and it seems to work fine on my laptop now.
  glEnable(GL_DEPTH_TEST);
  // Create the shader program
  Shader shader_program("vertex.shader", "fragment.shader");
  
  // Create an dbind the Vector array object
  VAO VAO1;
  VAO1.Bind();
  
  // Create VBO and EBO
  VBO VBO1{vertices, sizeof(vertices)/sizeof(float)};
  VBOLayout layout;
  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 2);
  VAO1.LinkVBO(VBO1, layout);

  VAO1.Unbind();
  VBO1.Unbind();
  Texture texture{"../resources/container.jpg", GL_TEXTURE_2D};
  texture.Bind();
  shader_program.SetUniform1i("u_texture", 0);
  
  Renderer renderer;

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
  ImGui::StyleColorsDark();
  float speed{};
  float pitch{};

  while(!glfwWindowShouldClose(window)) {
    float current_frame = glfwGetTime();
    dt = current_frame - last_frame;
    last_frame = current_frame;

    ProcessInput(window);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    shader_program.Use();
    VAO1.Bind();
    renderer.Clear();     
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glm::mat4 view;
    view = glm::lookAt(camera_pos, camera_pos+camera_front, camera_up);
    shader_program.SetMat4f("view", view);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f/800.0f, 0.001f, 1000.0f);
    shader_program.SetMat4f("projection", projection);

    for (uint32_t i = 0; i < 10; ++i) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      if (i % 3 == 0) {
        angle = glfwGetTime() * speed;
      }
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      shader_program.SetMat4f("model", model);

      renderer.Draw(VAO1, 36, shader_program);
    }


    ImGui::Begin("Demo window");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat("speed", &speed, 0.0f, 100.0f);
    ImGui::SliderFloat("pitch", &pitch, -89.0f, 89.0f);
    ImGui::SliderFloat("yaw", &yaw, -179.0f, 179.0f);
    ImGui::End();


    // direction = {cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
    //                 sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch))};

    // camera_front = glm::normalize(direction);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  shader_program.Delete();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  
  glfwTerminate();
}

auto FramebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int32_t width, int32_t height) -> void
{
  glViewport(0, 0, width, height);
}

auto ProcessInput(GLFWwindow* window) -> void
{
  const float camera_speed = 2.5f * dt;
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera_pos += camera_speed * camera_front;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera_pos -= camera_speed * camera_front;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
}

auto mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in) -> void
{

  float xpos = static_cast<float>(xpos_in);
  float ypos = static_cast<float>(ypos_in);

  if (first_mouse) {
    last_x = xpos;
    last_y = ypos;
    first_mouse = false;
  }

  float x_offset = xpos - last_x;
  float y_offset = last_y - ypos;
  last_x = xpos;
  last_y = ypos;

  const float sensitivity = 0.001f;
  x_offset *= sensitivity;
  y_offset *= sensitivity;
  
  yaw += x_offset;
  pitch += y_offset;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  // glm::vec3 direction = {cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
  //                   sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch))};
  // std::cout << "pitch = " << pitch << '\n';
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  
  camera_front = glm::normalize(direction);
}
