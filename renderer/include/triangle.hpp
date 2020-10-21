#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "mesh.hpp"
#include <glad/glad.h>

namespace renderer {
namespace mesh {

struct vertex_t {
  float x, y, z;
  float r, g, b;
};

/**
 * @brief Triangle mesh.
 * @note Test class, will dissapear in a near future.
 */
class Triangle : public Mesh {
public:
  explicit Triangle() noexcept;

  void render() const;
};

} // namespace mesh
} // namespace renderer

#endif // TRIANGLE_H
