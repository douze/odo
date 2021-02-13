#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "glm/glm.hpp"
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
  float snow_height = 0.35f;
  float snow_uv = 100.0f;
  float ground_height = 0.15f;
  float ground_uv = 20.0f;
  float grass_uv = 50.0f;
  float rock_uv = 10.0f;
  float mix_area_width = 0.1f;

  float edge0_rock_snow = 0.1;
  float edge1_rock_snow = 0.2;

  float edge0_rock_ground = 0.1;
  float edge1_rock_ground = 0.2;

  float edge0_rock_grass = 0.1;
  float edge1_rock_grass = 0.2;

  int display_type = 2;

  glm::vec3 light_position = glm::vec3{0.5f};

  GLuint grass_texture;
  GLuint ground_texture;
  GLuint rock_texture;
  GLuint snow_texture;
};

} // namespace odo::material

#endif // TERRAINMATERIAL_H
