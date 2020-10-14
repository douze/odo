#include "camera.hpp"
#include <glm/gtx/transform.hpp>
#include <iostream>

using namespace renderer::scene;

Camera::Camera(const glm::vec3& position, const int width,
               const int height) noexcept
    : position{position}, front{glm::vec3{0.0f, 0.0f, -1.0f}},
      up{glm::vec3{0.0f, 1.0f, 0.0f}}, right{glm::vec3{1.0f, 0.0f, 0.0f}},
      yaw{0.0f}, pitch{0.0f}, dirty{true},
      projectionMatrix{
          glm::perspective(45.0f, (float)(width / height), 1.0f, 500.0f)} {}

glm::mat4 Camera::getViewMatrix() {
  if (dirty) {
    dirty = false;
    viewMatrix = glm::lookAt(position, position + front, up);
  }
  return viewMatrix;
}

void Camera::move(Direction direction, float deltaTime) {
  dirty = true;
  const float velocity = 5.0f * deltaTime;
  if (direction == Direction::FORWARD) {
    position += front * velocity;
  }
  if (direction == Direction::BACKWARD) {
    position -= front * velocity;
  }
  if (direction == Direction::LEFT) {
    position -= right * velocity;
  }
  if (direction == Direction::RIGHT) {
    position += right * velocity;
  }
  std::cout << position.x << " " << position.y << " " << position.z
            << std::endl;
  std::cout << yaw << " " << pitch << std::endl;
}

void Camera::rotate(float x, float y, float deltaTime) {
  // TODO
}
