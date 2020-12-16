#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

namespace odo::mesh {

/**
 * @brief Base class for 3D meshes.
 */
class Mesh {
public:
  /**
   * @brief Prepare the mesh before the render loop.
   */
  virtual void prepare() {}

  /**
   * @brief Render the mesh using the current material.
   */
  virtual void render() const = 0;

  /**
   * @brief Render the mesh UI to the GUI frame.
   */
  virtual void render_ui() const {}

protected:
  /** Vertex array object */
  GLuint vao;
};

} // namespace odo::mesh

#endif // MESH_H
