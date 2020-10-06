#include "camera.hpp"
#include <glm/gtx/transform.hpp>

using namespace renderer::scene;

Camera::Camera(const glm::vec3& position, const int width,
               const int height) noexcept
    : position{position}, dirty{true}, projectionMatrix{glm::perspective(
                                           45.0f, (float)(width / height), 1.0f,
                                           500.0f)} {}

glm::mat4 Camera::getViewMatrix() {
  if (dirty) {
    dirty = false;
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, position);
  }
  return viewMatrix;
}
