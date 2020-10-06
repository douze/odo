#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace renderer {
namespace scene {

/**
 * @brief Virtual camera for viewer controller.
 */
class Camera {
public:
  /**
   * @brief Create a camera at the desired position.
   * @param position of the camera
   */
  explicit Camera(const glm::vec3& position, const int width, const int height) noexcept;

  /**
   * @brief Return the view matrix.
   */
  glm::mat4 getViewMatrix();
  
  /**
   * @brief Return the projection matrix.
   */
  glm::mat4 getProjectionMatrix() const { return projectionMatrix; }

private:
  /** Camera position */
  glm::vec3 position;

  /** View matrix */
  glm::mat4 viewMatrix;
  
  /** Projectino matrix */
  glm::mat4 projectionMatrix;

  /** True if recompute of view matrix is needed */
  bool dirty;
};

} // namespace scene
} // namespace renderer
#endif // CAMERA_H
