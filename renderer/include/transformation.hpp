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
   * @param rotation of the mesh
   * @param scale of the mesh
   */
  explicit Transformation(const glm::vec3& position, const glm::vec3& rotation = glm::vec3{0.0f},
                          const glm::vec3& scale = glm::vec3{1.0f}) noexcept;

  /**
   * @return the computed transformation matrix.
   */
  glm::mat4 get_matrix();

private:
  /** Position of the mesh */
  glm::vec3 position;

  /** Rotation of the mesh */
  glm::vec3 rotation;

  /** Scale of the mesh */
  glm::vec3 scale;

  /** Transformation matrix */
  glm::mat4 matrix;

  /** True if recompute is needed */
  bool dirty;
};

} // namespace odo::mesh

#endif // TRANSFORMATION_H
