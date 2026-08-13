#pragma once

#include <glm/glm.hpp>

enum CameraMovement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5;
const float SENS = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
  glm::vec3 Pos;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  float Yaw;
  float Pitch;

  float MoveSpeed;
  float MouseSens;
  float Zoom;

  Camera(glm::vec3 pos = glm::vec3 { 0.0f, 0.0f, 0.0f }, glm::vec3 up = glm::vec3 { 0.0f, 1.0f, 0.0f }, float yaw = YAW, float pitch = PITCH);
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

  glm::mat4 getViewMatrix();
  void processKeyboard(CameraMovement direction, float deltaTime);
  void processMouse(float xoffset, float yoffset, bool constrainPitch = true);
  void processScroll(float yoffset);
private:
  void updateCameraVectors();
};