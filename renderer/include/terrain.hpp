#ifndef TERRAIN_H
#define TERRAIN_H

#include "mesh.hpp"

namespace renderer {
namespace mesh {

struct TerrainVertex {
  float x, y;
  float r, g, b;
  float u, v;
};

/**
 * @brief 3D terrain using patches.
 */
class Terrain : public Mesh {
public:
  /**
   * @brief Create a terrain.
   */
  explicit Terrain() noexcept;

  /**
   * @note Generate the noise texture.
   */
  void prepare() override;

  void render() const override;

private:
  /** Noise texture */
  GLuint texture;
};

} // namespace mesh
} // namespace renderer

#endif // TERRAIN_H
