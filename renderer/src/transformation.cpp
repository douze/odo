#include "transformation.hpp"
#include <glm/gtx/transform.hpp>

using namespace renderer::mesh;

Transformation::Transformation(const glm::vec3& position) noexcept
    : position{position}, dirty{true} {}

glm::mat4 Transformation::getMatrix() {
  if (dirty) {
    dirty = false;
    matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
  }
  return matrix;
}