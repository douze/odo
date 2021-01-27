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
  float snow_height = 0.35;
  float grass_height = 0.15;
  float mix_area_width = 0.1;

  GLuint grass_texture;
  GLuint ground_texture;
  GLuint rock_texture;
  GLuint snow_texture;
};

} // namespace odo::material

#endif // TERRAINMATERIAL_H
