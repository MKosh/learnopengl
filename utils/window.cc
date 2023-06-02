#include <cstdint>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

Window::Window(uint32_t width, uint32_t height, const std::string name) {
  m_width = width;
  m_height = height;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, name.c_str(), nullptr, nullptr);
  if (!m_window) {
    std::cout << "ERROR: failed to initialize GLFW window\n";
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_window);
  glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
  glfwSetCursorPosCallback(m_window, mouse_callback);
  glfwSetScrollCallback(m_window, scroll_callback);
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetKeyCallback(m_window, interactive_callback);
 
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "ERROR: failed to initialize GLAD\n";
  }

  glViewport(0, 0, m_width, m_height); 
  glEnable(GL_DEPTH_TEST);
} 
