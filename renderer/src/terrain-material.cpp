#include "terrain-material.hpp"
#include "camera.hpp"
#include "noise-terrain-material.hpp"
#include "transformation.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <iostream>

using namespace odo::material;

TerrainMaterial::TerrainMaterial() noexcept
    : Material{"terrain.vs.glsl", "terrain.tcs.glsl", "terrain.tes.glsl", "terrain.gs.glsl", "terrain.fs.glsl"} {
  grass_texture = create_texture("grass_grass_0124_01_tiled_s.jpg", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
  ground_texture = create_texture("soil_ground_0045_02_tiled_s.jpg", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
  rock_texture = create_texture("rock_stones_0027_02_tiled_s.jpg", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
  snow_texture = create_texture("ground_stone_ground_0031_01_tiled.jpg", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
}

void TerrainMaterial::render_ui() {
  ImGui::Checkbox("Wireframe", &use_wireframe);
  ImGui::SliderFloat("Height factor", &height_factor, 0.0f, 100.0f);
  ImGui::SliderFloat("Scale XY", &patch_scale, 0.0f, 3.0f);
  ImGui::SliderFloat("Mix area width", &mix_area_width, 0.0f, 1.0f);

  if (ImGui::BeginTable("Textures", 3, ImGuiTableFlags_Borders)) {
    ImGui::TableSetupColumn("Snow");
    ImGui::TableSetupColumn("Ground");
    ImGui::TableSetupColumn("Grass");
    ImGui::TableHeadersRow();

    ImGui::TableNextColumn();
    ImGui::SliderFloat("Height##snow", &snow_height, 0.0f, 1.0f);
    ImGui::SliderFloat("UV##snow", &snow_uv, 0.0f, 200.0f);

    ImGui::Text("Rock");
    ImGui::SliderFloat("Edge 0##snow", &edge0_rock_snow, 0.0f, 1.0f);
    ImGui::SliderFloat("Edge 1##snow", &edge1_rock_snow, 0.0f, 1.0f);
    ImGui::SliderFloat("UV##snow", &rock_uv, 0.0f, 200.0f);

    ImGui::TableNextColumn();
    ImGui::SliderFloat("Height##ground", &ground_height, 0.0f, 1.0f);
    ImGui::SliderFloat("UV##ground", &ground_uv, 0.0f, 200.0f);

    ImGui::Text("Rock");
    ImGui::SliderFloat("Edge 0##ground", &edge0_rock_ground, 0.0f, 1.0f);
    ImGui::SliderFloat("Edge 1##ground", &edge1_rock_ground, 0.0f, 1.0f);
    ImGui::SliderFloat("UV##ground", &rock_uv, 0.0f, 200.0f);

    ImGui::TableNextColumn();
    ImGui::SliderFloat("UV##grass", &grass_uv, 0.0f, 200.0f);

    ImGui::EndTable();
  }

  ImGui::Text("Albedo");
  ImGui::RadioButton("HeightMap", &display_type, 0);
  ImGui::RadioButton("NormalMap", &display_type, 1);
  ImGui::RadioButton("ColorMap", &display_type, 2);

  ImGui::Text("Light");
  ImGui::SliderFloat("Light X", &light_position[0], 0.0f, 1.0f);
  ImGui::SliderFloat("Light Y", &light_position[1], 0.0f, 2.0f);
  ImGui::SliderFloat("Light Z", &light_position[2], 0.0f, 3.0f);
}

void TerrainMaterial::set_uniforms() const {
  glProgramUniform1ui(fs, 0, use_wireframe);
  glProgramUniform1f(fs, 1, snow_height);
  glProgramUniform1f(fs, 2, ground_height);
  glProgramUniform1f(fs, 3, mix_area_width);

  glProgramUniform1f(fs, 4, edge0_rock_snow);
  glProgramUniform1f(fs, 5, edge1_rock_snow);

  glProgramUniform1i(fs, 6, display_type);

  glProgramUniform3f(fs, 7, light_position[0], light_position[1], light_position[2]);

  glProgramUniform1f(fs, 10, snow_uv);
  glProgramUniform1f(fs, 11, ground_uv);
  glProgramUniform1f(fs, 12, grass_uv);
  glProgramUniform1f(fs, 13, rock_uv);

  glProgramUniform1f(fs, 14, edge0_rock_ground);
  glProgramUniform1f(fs, 15, edge1_rock_ground);

  glProgramUniform1f(fs, 16, edge0_rock_grass);
  glProgramUniform1f(fs, 17, edge1_rock_grass);

  glProgramUniform1f(tes, 0, height_factor);

  glProgramUniform1i(vs, 3, grid_size);
  glProgramUniform1f(vs, 4, patch_scale);
  glProgramUniform1f(vs, 5, patch_size);
}

void TerrainMaterial::set_uniforms_from_parent(const Material& parent_material) const {
  const NoiseTerrainMaterial& noise_terrain_material = dynamic_cast<const NoiseTerrainMaterial&>(parent_material);
  glBindTextureUnit(0, noise_terrain_material.get_offscreen_texture());
  glBindTextureUnit(1, grass_texture);
  glBindTextureUnit(2, ground_texture);
  glBindTextureUnit(3, rock_texture);
  glBindTextureUnit(4, snow_texture);
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
