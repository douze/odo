#include "terrain-material.hpp"
#include <imgui.h>

using namespace odo::material;

TerrainMaterial::TerrainMaterial() noexcept
    : Material{"terrain.vs.glsl", "terrain.tcs.glsl", "terrain.tes.glsl", "terrain.gs.glsl", "terrain.fs.glsl"} {}

void TerrainMaterial::render_ui() { ImGui::Checkbox("Wireframe", &use_wireframe); }

void TerrainMaterial::set_uniforms() const { glProgramUniform1ui(fs, 0, use_wireframe); }
