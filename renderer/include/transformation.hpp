#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/glm.hpp>

namespace odo::mesh {

/**
 * @brief Represent a 3D transformation.
 */
class Transformation {
public:
  /**
   * @brief Create a transformation.
   * @param position of the mesh
   */
  explicit Transformation(const glm::vec3& position) noexcept;

  /**
   * @brief Return the computed transformation matrix.
   */
  glm::mat4 getMatrix();

  /**
   * @brief Return the position by const reference.
   */
  const glm::vec3& getPosition() const { return position; }

private:
  /** Position of the mesh */
  glm::vec3 position;

  /** Transformation matrix */
  glm::mat4 matrix;

  /** True if recompute is needed */
  bool dirty;
};

} // namespace odo::mesh

#endif // TRANSFORMATION_H
