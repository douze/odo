#include "transformation.hpp"
#include <glm/gtx/transform.hpp>

using namespace odo::mesh;

Transformation::Transformation(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) noexcept
    : position{position}, rotation{rotation}, scale{scale}, dirty{true} {}

glm::mat4 Transformation::get_matrix() {
  if (dirty) {
    dirty = false;
    matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3{1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3{0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3{0, 0, 1});
    matrix = glm::scale(matrix, scale);
  }
  return matrix;
}
