#include "terrain-material.hpp"
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
}
