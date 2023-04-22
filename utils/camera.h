#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum class CameraMovement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.005;
const float ZOOM        = 45.0f;

class Camera {
private:
  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_world_up;

  float m_yaw;
  float m_pitch;
  float m_movement_speed;
  float m_mouse_sensitivity;
  float m_zoom;

  auto UpdateCameraVectors() -> void;

public:
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float yaw = YAW, float pitch = PITCH);
          
  Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);

  auto GetViewMatrix() const -> glm::mat4;
  auto ProcessKeyboard(CameraMovement direction, float delta_time) -> void;
  auto ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch = true) -> void;
  auto ProcessMouseScroll(float y_offset) -> void;
  auto GetZoom() const -> float {return m_zoom;}
  auto GetYaw() -> float {return m_yaw;}
  auto GetPitch() -> float {return m_pitch;}
};

