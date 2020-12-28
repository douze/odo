#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "material.hpp"

namespace odo::material {

/**
 * @brief Material used for the terrain (using precomputed noise heightmap).
 */
class TerrainMaterial : public Material {
public:
  explicit TerrainMaterial() noexcept;

  void render_ui() override;

  void set_uniforms() const override;

  int grid_size = 1;
  float scale_xy = 1.0f;

private:
  bool use_wireframe = false;
  float height_factor = 10.0f;
};

} // namespace odo::material

#endif // TERRAINMATERIAL_H
