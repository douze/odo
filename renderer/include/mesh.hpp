#ifndef MESH_H
#define MESH_H

namespace renderer {
namespace mesh {
/**
 * @todo write docs
 */
class Mesh {
public:
  virtual void render() const = 0;
};

} // namespace mesh
} // namespace renderer

#endif // MESH_H
