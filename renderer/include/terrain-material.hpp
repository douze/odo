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
  void set_uniforms_from_parent(const Material& parent_material) const override;

  void set_camera_matrices(scene::Camera camera) const override;
  void set_transformation_matrix(mesh::Transformation transformation) const override;

  int grid_size = 1;
  float patch_scale = 1.0f;
  float patch_size = 1.0f;

private:
  bool use_wireframe = false;
  float height_factor = 1.5f;
};

} // namespace odo::material

#endif // TERRAINMATERIAL_H
