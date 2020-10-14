#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace renderer {
namespace scene {

enum class Direction { FORWARD, BACKWARD, LEFT, RIGHT };

/**
 * @brief Virtual camera for viewer controller.
 */
class Camera {
public:
  /**
   * @brief Create a camera at the desired position.
   * @param position of the camera
   */
  explicit Camera(const glm::vec3& position, const int width,
                  const int height) noexcept;

  /**
   * @brief Return the view matrix.
   */
  glm::mat4 getViewMatrix();

  /**
   * @brief Return the projection matrix.
   */
  glm::mat4 getProjectionMatrix() const { return projectionMatrix; }
  
  /**
   * @brief Move the camera.
   * @param direction to follow
   * @param deltaTime from previous update
   */
  void move(Direction direction, float deltaTime);
  
  /**
   * @brief Rotate the camera.
   * @param x offset
   * @param y offset
   * @param deltaTime from previous update
   */
  void rotate(float x, float y, float deltaTime);

private:
  /** Camera position */
  glm::vec3 position;
  
  /** Front vector */
  glm::vec3 front;
  
  /** Up vector */
  glm::vec3 up;
  
  /** Right vector */
  glm::vec3 right;
  
  /** Yaw rotation (x axis) */
  float yaw;
  
  /** Pitch rotation (y axis) */
  float pitch;

  /** View matrix */
  glm::mat4 viewMatrix;

  /** Projection matrix */
  glm::mat4 projectionMatrix;

  /** True if recompute of view matrix is needed */
  bool dirty;
};

} // namespace scene
} // namespace renderer
#endif // CAMERA_H