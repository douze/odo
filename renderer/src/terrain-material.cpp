#include "terrain-material.hpp"
#include "camera.hpp"
#include "transformation.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

using namespace odo::material;

TerrainMaterial::TerrainMaterial() noexcept
    : Material{"terrain.vs.glsl", "terrain.tcs.glsl", "terrain.tes.glsl", "terrain.gs.glsl", "terrain.fs.glsl"} {}

void TerrainMaterial::render_ui() {
  ImGui::Checkbox("Wireframe", &use_wireframe);
  ImGui::SliderFloat("Height factor", &height_factor, 0.0f, 100.0f);
  ImGui::SliderFloat("Scale XY", &scale_xy, 0.0f, 3.0f);
}

void TerrainMaterial::set_uniforms() const {
  glProgramUniform1ui(fs, 0, use_wireframe);
  glProgramUniform1f(tes, 0, height_factor);
  glProgramUniform1i(vs, 3, grid_size);
  glProgramUniform1f(vs, 4, scale_xy);
  glProgramUniform1f(vs, 5, patch_size);
}

void TerrainMaterial::set_uniforms_from_parent(const Material& parent_material) const {
  glBindTextureUnit(0, parent_material.get_offscreen_texture());
}

void TerrainMaterial::set_camera_matrices(scene::Camera camera) const {
  Material::set_camera_matrices(camera);
  glProgramUniformMatrix4fv(tcs, 1, 1, GL_FALSE, glm::value_ptr(camera.get_view_matrix()));
  glProgramUniform3fv(tcs, 2, 1, glm::value_ptr(camera.get_position()));

  glProgramUniformMatrix4fv(tes, 1, 1, GL_FALSE, glm::value_ptr(camera.get_view_matrix()));
  glProgramUniformMatrix4fv(tes, 2, 1, GL_FALSE, glm::value_ptr(camera.get_projection_matrix()));
}

void TerrainMaterial::set_transformation_matrix(mesh::Transformation transformation) const {
  Material::set_transformation_matrix(transformation);
  glProgramUniformMatrix4fv(tcs, 0, 1, GL_FALSE, glm::value_ptr(transformation.get_matrix()));
}
