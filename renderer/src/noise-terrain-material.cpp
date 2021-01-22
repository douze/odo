#include "noise-terrain-material.hpp"
#include <imgui.h>

using namespace odo::material;

NoiseTerrainMaterial::NoiseTerrainMaterial() noexcept : Material{"noise-terrain.vs.glsl", "noise-terrain.fs.glsl"} {}

void NoiseTerrainMaterial::prepare(const int width, const int height) {
  // FBO
  glCreateFramebuffers(1, &fbo);

  // Texture
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glTextureStorage2D(texture, 1, GL_RGB8, width, height);
  glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, 0);
  //   glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //   glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, texture, 0);
}

void NoiseTerrainMaterial::add_combo(const char* label, int* current_item, const char* items_separated_by_zeros) {
  if (ImGui::Combo(label, current_item, items_separated_by_zeros)) {
    dirty = true;
  }
}

void NoiseTerrainMaterial::add_checkbox(const char* label, bool* v) {
  if (ImGui::Checkbox(label, v)) {
    dirty = true;
  }
}

void NoiseTerrainMaterial::add_input_scalar(const char* label, void* p_data, const void* p_step) {
  if (ImGui::InputScalar(label, ImGuiDataType_Float, p_data, p_step)) {
    dirty = true;
  }
}

void NoiseTerrainMaterial::add_slider_int(const char* label, int* v, int v_min, int v_max) {
  if (ImGui::SliderInt(label, v, v_min, v_max)) {
    dirty = true;
  }
}

void NoiseTerrainMaterial::render_ui() {
  add_combo("Noise function", &noise_function, "Simplex\0Billow\0Ridged\0Heightmap\0\0");
  add_checkbox("Use demo value", &use_demo_value);

  float step = 0.1f;
  ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
  if (ImGui::BeginTabBar("NoiseTabs", tab_bar_flags)) {
    if (ImGui::BeginTabItem("Simplex")) {
      add_slider_int("Octaves##fbm", &fbm_octaves, 1.0f, 8.0f);
      ImGui::PushItemWidth(120);
      add_input_scalar("Amplitude##fbm", &fbm_amplitude_persistence[0], &step);
      ImGui::SameLine();
      add_input_scalar("Persistency##fbm", &fbm_amplitude_persistence[1], &step);
      add_input_scalar("Frequency##fbm", &fbm_frequency_lacunarity[0], &step);
      ImGui::SameLine();
      add_input_scalar("Lacunarity##fbm", &fbm_frequency_lacunarity[1], &step);
      ImGui::PopItemWidth();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Billow")) {
      add_slider_int("Octaves##billow", &billow_octaves, 1.0f, 8.0f);
      ImGui::PushItemWidth(120);
      add_input_scalar("Amplitude##billow", &billow_amplitude_persistence[0], &step);
      ImGui::SameLine();
      add_input_scalar("Persistency##billow", &billow_amplitude_persistence[1], &step);
      add_input_scalar("Frequency##billow", &billow_frequency_lacunarity[0], &step);
      ImGui::SameLine();
      add_input_scalar("Lacunarity##billow", &billow_frequency_lacunarity[1], &step);
      ImGui::PopItemWidth();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Ridged Multi")) {
      add_slider_int("Octaves##rmf", &rmf_octaves, 1.0f, 8.0f);
      ImGui::PushItemWidth(120);
      add_input_scalar("Amplitude##rmf", &rmf_amplitude_persistence[0], &step);
      ImGui::SameLine();
      add_input_scalar("Persistency##rmf", &rmf_amplitude_persistence[1], &step);
      add_input_scalar("Frequency##rmf", &rmf_frequency_lacunarity[0], &step);
      ImGui::SameLine();
      add_input_scalar("Lacunarity##rmf", &rmf_frequency_lacunarity[1], &step);
      add_input_scalar("H##rmf", &rmf_h_offset[0], &step);
      ImGui::SameLine();
      add_input_scalar("Offset##rmf", &rmf_h_offset[1], &step);
      ImGui::PopItemWidth();
      ImGui::EndTabItem();
    }
  }
  ImGui::EndTabBar();

  ImGui::Text("Noise texture");
  ImGui::Image((void*)(intptr_t)texture, ImVec2(400, 400), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}

void NoiseTerrainMaterial::set_uniforms() const {
  glProgramUniform1i(fs, 0, fbm_octaves);
  glProgramUniform2f(fs, 1, fbm_amplitude_persistence[0], fbm_amplitude_persistence[1]);
  glProgramUniform2f(fs, 2, fbm_frequency_lacunarity[0], fbm_frequency_lacunarity[1]);

  glProgramUniform1i(fs, 3, billow_octaves);
  glProgramUniform2f(fs, 4, billow_amplitude_persistence[0], billow_amplitude_persistence[1]);
  glProgramUniform2f(fs, 5, billow_frequency_lacunarity[0], billow_frequency_lacunarity[1]);

  glProgramUniform1i(fs, 6, rmf_octaves);
  glProgramUniform2f(fs, 7, rmf_amplitude_persistence[0], rmf_amplitude_persistence[1]);
  glProgramUniform2f(fs, 8, rmf_frequency_lacunarity[0], rmf_frequency_lacunarity[1]);
  glProgramUniform2f(fs, 9, rmf_h_offset[0], rmf_h_offset[1]);

  glProgramUniform1ui(fs, 11, use_demo_value);
  glProgramUniform1i(fs, 12, noise_function);
}
