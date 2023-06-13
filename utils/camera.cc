#include "camera.h"

#include <cmath>
#include <exception>
#include <glad/glad.h>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
          : m_position{position}, m_world_up{up}, m_yaw{yaw}, m_pitch{pitch}, m_front{glm::vec3(0.0f, 0.0f, -1.0f)}, m_movement_speed(SPEED), m_mouse_sensitivity(SENSITIVITY), m_zoom(ZOOM)
{
  UpdateCameraVectors();
}


Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
          : m_front{glm::vec3(0.0f, 0.0f, -1.0f)}, m_movement_speed(SPEED), m_mouse_sensitivity(SENSITIVITY), m_zoom(ZOOM)
{
  UpdateCameraVectors(); 
}

auto Camera::GetViewMatrix() const -> glm::mat4 {
  return glm::lookAt(m_position, m_position + m_front, m_up);
}

auto Camera::GetPosition() const -> glm::vec3 {
  return m_position;
}

auto Camera::ProcessKeyboard(CameraMovement direction, float delta_time) -> void {
  float velocity = m_movement_speed * delta_time;
  if (direction == CameraMovement::FORWARD)
    m_position += m_front * velocity;
  if (direction == CameraMovement::BACKWARD)
    m_position -= m_front * velocity;
  if (direction == CameraMovement::LEFT)
    m_position -= m_right * velocity;
  if (direction == CameraMovement::RIGHT)
    m_position += m_right * velocity;
}

auto Camera::ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch)-> void {
  x_offset *= m_mouse_sensitivity;
  y_offset *= m_mouse_sensitivity;

  m_yaw += x_offset;
  m_pitch += y_offset;

  if (constrain_pitch) {
    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
  }

  UpdateCameraVectors();
}

auto Camera::ProcessMouseScroll(float y_offset) -> void {
  m_zoom -= (float)y_offset;
  if (m_zoom < 1.0f) m_zoom = 1.0f;
  if (m_zoom > 45.0f) m_zoom = 45.0f;
}

auto Camera::UpdateCameraVectors() -> void {
  using namespace std;
  using namespace glm;
  glm::vec3 front{cos(radians(m_yaw)) * cos(radians(m_pitch)),
                  sin(radians(m_pitch)),
                  sin(radians(m_yaw)) * cos(radians(m_pitch))};

  m_front = normalize(front);
  m_right = normalize(cross(m_front, m_world_up));
  m_up    = normalize(cross(m_right, m_front));
}




