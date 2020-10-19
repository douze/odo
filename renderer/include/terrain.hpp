#ifndef TERRAIN_H
#define TERRAIN_H

#include "mesh.hpp"
#include <glad/glad.h>

namespace renderer {
namespace mesh {

struct TerrainVertex {
  float x, y;
  float r, g, b;
};

class Terrain : public Mesh {
public:
  explicit Terrain() noexcept;

  void render() const;

private:
  GLuint vao;
  GLuint program;
};
} // namespace mesh
} // namespace renderer
#endif // TERRAIN_H
