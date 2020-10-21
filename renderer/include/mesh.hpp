#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

namespace renderer {
namespace mesh {
  
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
protected:
  /** Vertex array object */
  GLuint vao;
};

} // namespace mesh
} // namespace renderer

#endif // MESH_H
