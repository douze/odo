#ifndef MESH_H
#define MESH_H

#include "gui-provider.hpp"
#include <glad/glad.h>

namespace odo::mesh {

/**
 * @brief Base class for 3D meshes.
 */
class Mesh : public odo::GuiProvider {
public:
  /**
   * @brief Prepare the mesh before the render loop.
   */
  virtual void prepare() {}

  /**
   * @brief Render the mesh using the current material.
   */
  virtual void render() const = 0;

  void render_ui() override {}

protected:
  /** Vertex array object */
  GLuint vao;
};

} // namespace odo::mesh

#endif // MESH_H
