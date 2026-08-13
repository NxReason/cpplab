#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 up , float yaw, float pitch)
  : Front(glm::vec3 { 0.0f, 0.0f, -1.0f }), MoveSpeed(SPEED), MouseSens(SENS), Zoom(ZOOM) {
  Pos = pos;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
  : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(SPEED), MouseSens(SENS), Zoom(ZOOM) {
  Pos = glm::vec3(posX, posY, posZ);
  WorldUp = glm::vec3(upX, upY, upZ);
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(Pos, Pos + Front, Up);
}
void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
  float velocity = MoveSpeed * deltaTime;
  if (direction == FORWARD)
      Pos += Front * velocity;
  if (direction == BACKWARD)
      Pos -= Front * velocity;
  if (direction == LEFT)
      Pos -= Right * velocity;
  if (direction == RIGHT)
      Pos += Right * velocity;
}

void Camera::processMouse(float xoffset, float yoffset, bool constrainPitch) {
  xoffset *= MouseSens;
  yoffset *= MouseSens;

  Yaw   += xoffset;
  Pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch)
  {
      if (Pitch > 89.0f)
          Pitch = 89.0f;
      if (Pitch < -89.0f)
          Pitch = -89.0f;
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

void Camera::processScroll(float yoffset) {
  Zoom -= (float)yoffset;
  if (Zoom < 1.0f)
      Zoom = 1.0f;
  if (Zoom > 45.0f)
      Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(front);
  // also re-calculate the Right and Up vector
  Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  Up    = glm::normalize(glm::cross(Right, Front));
}
