#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace odo::scene {

enum class Direction { FORWARD, BACKWARD, LEFT, RIGHT };

/**
 * @brief Virtual camera for viewer controller.
 */
class Camera {
public:
  /**
   * @brief Create a camera at the desired position.
   * @param position of the camera
   * @param aspect for pespective projection
   */
  explicit Camera(const glm::vec3& position, float aspect) noexcept;

  /**
   * @return the view matrix.
   */
  glm::mat4 get_view_matrix();

  /**
   * @return the projection matrix.
   */
  glm::mat4 get_projection_matrix() const { return projection_matrix; }

  /**
   * @brief Move the camera along a direction.
   * @param direction to follow
   * @param delta time from previous update
   */
  void move(Direction direction, float delta_time);

  /**
   * @brief Rotate the camera.
   * @param x offset
   * @param y offset
   * @param delta time from previous update
   */
  void rotate(float x, float y, float delta_time);

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
  glm::mat4 view_matrix;

  /** Projection matrix */
  glm::mat4 projection_matrix;

  /** True if recompute of view matrix is needed */
  bool dirty;
};

} // namespace odo::scene

#endif // CAMERA_H
