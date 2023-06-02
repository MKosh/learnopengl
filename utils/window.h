#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>


///////////////////////////////////////////////////////////////////////////////
/// Function declarations
auto FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) -> void;
auto ProcessInput(GLFWwindow* window) -> void;
auto mouse_callback(GLFWwindow* window, double xpos, double ypos) -> void;
auto scroll_callback(GLFWwindow* window, double xpos, double ypos) -> void;
auto interactive_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void;


class Window {
public:
  Window(uint32_t width, uint32_t height, const std::string name);
  GLFWwindow* GetWindow() {return m_window;}
private:
  uint32_t m_width;
  uint32_t m_height;
  GLFWwindow* m_window;
  
};
