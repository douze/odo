#include "camera.hpp"
#include <glm/gtx/transform.hpp>

using namespace odo::scene;

Camera::Camera(const glm::vec3& position, float aspect) noexcept
    : position{position},
      front{glm::vec3{0.0f, 0.0f, -1.0f}},
      up{glm::vec3{0.0f, 1.0f, 0.0f}},
      right{glm::vec3{1.0f, 0.0f, 0.0f}},
      yaw{-90.0f},
      pitch{0.0f},
      projection_matrix{glm::perspective(45.0f, aspect, 0.1f, 500.0f)},
      dirty{true} {}

glm::mat4 Camera::get_view_matrix() {
  if (dirty) {
    dirty = false;
    view_matrix = glm::lookAt(position, position + front, up);
  }
  return view_matrix;
}

void Camera::move(Direction direction, float delta_time) {
  dirty = true;

  const float velocity = 5.0f * delta_time;
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
}

void Camera::rotate(float x, float y) {
  dirty = true;

  yaw += x * 0.1;
  pitch += y * 0.1;

  front = glm::normalize(glm::vec3{cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)),
                                   sin(glm::radians(yaw)) * cos(glm::radians(pitch))});
  right = glm::normalize(glm::cross(front, glm::vec3{0.0f, 1.0f, 0.0f}));
  up = glm::normalize(glm::cross(right, front));
}
