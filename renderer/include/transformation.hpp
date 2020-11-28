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
   * @return the computed transformation matrix.
   */
  glm::mat4 get_matrix();

  /**
   * @return the position.
   */
  const glm::vec3& get_position() const { return position; }

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
