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

private:
  bool use_wireframe = false;
};

} // namespace odo::material

#endif // TERRAINMATERIAL_H
