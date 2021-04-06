#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "glm/glm.hpp"
#include "material.hpp"

namespace odo::material {

struct TerrainSubMaterial {
  float height;
  GLuint primary_texture;
  float primary_uv;
  GLuint secondary_texture;
  float secondary_uv;
  float edge0;
  float edge1;
};

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
  float mix_area_width = 0.1f;
  int display_type = 2;
  glm::vec3 light_position = glm::vec3{0.5f};

  TerrainSubMaterial snow_material{0.35f, 0, 5.0f, 0, 10.0f, 0.1f, 0.2f};
  TerrainSubMaterial ground_material{0.15f, 0, 20.0f, 0, 0.0f, 0.0f, 0.0f};
  TerrainSubMaterial grass_material{0.0f, 0, 20.0f, 0, 10.0f, 0.8f, 0.9f};
};

} // namespace odo::material

#endif // TERRAINMATERIAL_H
