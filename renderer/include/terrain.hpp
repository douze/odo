#ifndef TERRAIN_H
#define TERRAIN_H

#include "mesh.hpp"

namespace odo::mesh {

struct TerrainVertex {
  float x, y;
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

  void render() const override;

  int instance_count = 1;
  float patch_size = 1.0f;

  float get_patch_size() const { return patch_size; }

private:
  /** Noise texture */
  GLuint texture;
};

} // namespace odo::mesh

#endif // TERRAIN_H
