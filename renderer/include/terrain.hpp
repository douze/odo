#ifndef TERRAIN_H
#define TERRAIN_H

#include "mesh.hpp"

namespace odo::mesh {

struct TerrainVertex {
  float x, y;
  float u, v;
};

/**
 * @brief 3D terrain using patches.
 */
class Terrain : public Mesh {
public:
  /**
   * @brief Create a terrain.
   * @param path_size
   */
  explicit Terrain(const int patch_size) noexcept;

  void render() const override;

private:
  /** Noise texture */
  GLuint texture;
};

} // namespace odo::mesh

#endif // TERRAIN_H
