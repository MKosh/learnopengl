#include <cstdint>
#include <cstdlib>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "stb_image.h"

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shader.h"
#include "VBOLayout.h"
#include "texture.h"
#include "Renderer.h"
#include "camera.h"
#include "window.h"

const uint32_t win_width = 1280;
const uint32_t win_height = 720;

float vertices[] = {
  // positions          // normal coords
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
   0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

///////////////////////////////////////////////////////////////////////////////
/// Config stuff - initial settings
glm::vec3 cube(-0.5f,  -1.0f,  -1.5f); 
glm::vec3 light_pos( 0.0f,  0.1f, -5.0f); 

bool first_mouse = true;
bool interactive = true;
float dt = 0.0f;
float last_frame = 0.0f;
float last_x = win_width/2.0;
float last_y = win_height/2.0;
Camera camera{glm::vec3{0.0f, 0.0f, 3.0f}};
float yaw = camera.GetYaw();
float pitch = camera.GetPitch();

///////////////////////////////////////////////////////////////////////////////
/// Function declarations
auto FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) -> void;
auto ProcessInput(GLFWwindow* window) -> void;
auto mouse_callback(GLFWwindow* window, double xpos, double ypos) -> void;
auto scroll_callback(GLFWwindow* window, double xpos, double ypos) -> void;
auto interactive_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void;

int main(){
  Window win{win_width, win_height, "lighting"};
  auto window = win.GetWindow();

  /////////////////////////////////////////////////////////////////////////////
  // Create the shader program
  Shader color_cube_s("color_cube.vert", "color_cube.frag");
  Shader light_cube_s{"light_cube.vert", "light_cube.frag"}; 

  /////////////////////////////////////////////////////////////////////////////
  // Create and bind the Vector array objects
  VAO cube_vao, light_vao;
  cube_vao.Bind();
  
  /////////////////////////////////////////////////////////////////////////////
  // Create VBO and EBO for the colored cube
  VBO cube_data{vertices, sizeof(vertices)/sizeof(float)};
  VBOLayout layout;
  layout.Push(GL_FLOAT, 3);
  layout.Push(GL_FLOAT, 3);
  cube_vao.LinkVBO(cube_data, layout);

  cube_vao.Unbind();
  cube_data.Unbind();

  /////////////////////////////////////////////////////////////////////////////
  // Configure the light
  light_vao.Bind();
  light_vao.LinkVBO(cube_data, layout);

  Renderer renderer;

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
  ImGui::StyleColorsDark();
  float speed{};
  float pitch{};

  while(!glfwWindowShouldClose(window)) {
    float current_frame = (float)glfwGetTime();
    dt = current_frame - last_frame;
    last_frame = current_frame;
    // std::srand(std::time(0));

    ProcessInput(window);
    
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    renderer.Clear();     
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    color_cube_s.Use();
    // color_cube_s.SetVec3f("object_color", 1.0f, 0.5f, 0.31f);
    // color_cube_s.SetVec3f("light_color", 1.0f, 1.0f, 1.0f);

    // Setting materials
    color_cube_s.SetVec3f("material.ambient", 1.0f, 0.5f, 0.31f);
    color_cube_s.SetVec3f("material.diffuse", 1.0f, 0.5f, 0.31f);
    color_cube_s.SetVec3f("material.specular", 0.5f, 0.5f, 0.5f);
    color_cube_s.SetFloat("material.shininess", 32.0f);
    // color_cube_s.SetVec3f("material.ambient", 1.0f, 1.0f, 1.0f);
    // color_cube_s.SetVec3f("material.diffuse", 1.0f, 1.0f, 1.0f);
    // color_cube_s.SetVec3f("material.specular", 1.0f, 1.0f, 1.0f);
    // color_cube_s.SetFloat("material.shininess", 32.0f);

    // Set lighting
    // RGB unicorn vomit
    glm::vec3 lightColor;
    lightColor.x = 1.0f;//sin(glfwGetTime() * 2.0f);
    lightColor.y = 1.0f;//sin(glfwGetTime() * 0.7f);
    lightColor.z = 1.0f;//sin(glfwGetTime() * 1.3f);

    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.3f);

    color_cube_s.SetVec3f("light.ambient", ambientColor);
    color_cube_s.SetVec3f("light.diffuse", diffuseColor);
    color_cube_s.SetVec3f("light.specular", lightColor);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(win_width)/(float)win_height, 0.1f, 1000.0f);
    
    model = glm::translate(model, cube);
    
    color_cube_s.SetMat4f("view", view);
    color_cube_s.SetMat4f("projection", projection);
    color_cube_s.SetMat4f("model", model);
    color_cube_s.SetVec3f("view_pos", camera.GetPosition());

    float radius = 5.0f;
    glm::vec3 moved_light{radius*std::cos(speed*0.1*current_frame)+light_pos.x, light_pos.y, radius*std::sin(speed*0.1*current_frame)+light_pos.z};
    
    color_cube_s.SetVec3f("light_pos", moved_light);

    renderer.Draw(cube_vao, sizeof(vertices), color_cube_s);

    light_cube_s.Use();
    light_cube_s.SetMat4f("projection", projection);
    light_cube_s.SetMat4f("view", view);

    light_cube_s.SetVec3f("light.diffuse", lightColor);

    model = glm::mat4(1.0f);
    model = glm::translate(model, moved_light);
    model = glm::scale(model, glm::vec3(0.2f));

    light_cube_s.SetMat4f("model", model);

    renderer.Draw(light_vao, sizeof(vertices), light_cube_s);

    // // second light
    // model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 1.0f));
    // model = glm::scale(model, glm::vec3(0.2f));

    // light_cube_s.SetMat4f("model", model);

    // light_cube_s.SetVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
    // light_cube_s.SetVec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
    // light_cube_s.SetVec3f("light.specular", 1.0f, 1.0f, 1.0f);

    // renderer.Draw(light_vao, sizeof(vertices), light_cube_s);

    ImGui::Begin("Demo window");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat("speed", &speed, 0.0f, 100.0f);
    ImGui::SliderFloat("pitch", &pitch, -89.0f, 89.0f);
    ImGui::SliderFloat("yaw", &yaw, -179.0f, 179.0f);
    ImGui::End();

    pitch = camera.GetPitch();
    yaw = camera.GetYaw();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }


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
    camera.ProcessKeyboard(CameraMovement::FORWARD, dt);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::BACKWARD, dt);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::LEFT, dt);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::RIGHT, dt);
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

  camera.ProcessMouseMovement(x_offset, y_offset);
}

auto scroll_callback(GLFWwindow* window, double xpos, double ypos) -> void {
  camera.ProcessMouseScroll(static_cast<float>(ypos));
}

auto interactive_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
  if (key == GLFW_KEY_I && action == GLFW_PRESS) {
    if (interactive == true) {
      interactive = false;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
      interactive = true;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
  }
}
