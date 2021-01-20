#include "camera.hpp"
#include <glm/gtx/transform.hpp>
#include <imgui.h>

using namespace odo::scene;

Camera::Camera(const glm::vec3& position, const glm::vec2& orientation, const int width, const int height) noexcept
    : position{position},
      front{glm::vec3{0.0f, 0.0f, -1.0f}},
      up{glm::vec3{0.0f, 1.0f, 0.0f}},
      right{glm::vec3{1.0f, 0.0f, 0.0f}},
      yaw{orientation.x},
      pitch{orientation.y},
      projection_matrix{glm::perspective(45.0f, width / static_cast<float>(height), 0.1f, 500.0f)},
      dirty{true},
      window_width{width},
      window_height{height} {
  update_vectors();
}

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

  update_vectors();
}

void Camera::render_ui() const {
  if (ImGui::CollapsingHeader("Camera")) {
    ImGui::Text("x: %f", position.x);
    ImGui::SameLine();
    ImGui::Text("y: %f", position.y);
    ImGui::SameLine();
    ImGui::Text("z: %f", position.z);

    ImGui::Text("yaw: %f", yaw);
    ImGui::SameLine();
    ImGui::Text("pitch: %f", pitch);
  }
}

void Camera::update_vectors() {
  front = glm::normalize(glm::vec3{cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)),
                                   sin(glm::radians(yaw)) * cos(glm::radians(pitch))});
  right = glm::normalize(glm::cross(front, glm::vec3{0.0f, 1.0f, 0.0f}));
  up = glm::normalize(glm::cross(right, front));
}
