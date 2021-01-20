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

void NoiseTerrainMaterial::render_ui() {
  ImGui::Combo("Noise function", &noise_function, "Simplex\0Billow\0Ridged\0Heightmap\0\0");
  ImGui::Checkbox("Use demo value", &use_demo_value);

  float step = 0.1f;
  ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
  if (ImGui::BeginTabBar("NoiseTabs", tab_bar_flags)) {
    if (ImGui::BeginTabItem("Simplex")) {
      ImGui::SliderInt("Octaves##fbm", &fbm_octaves, 1.0f, 8.0f);
      ImGui::PushItemWidth(120);
      ImGui::InputScalar("Amplitude##fbm", ImGuiDataType_Float, &fbm_amplitude_persistence[0], &step);
      ImGui::SameLine();
      ImGui::InputScalar("Persistency##fbm", ImGuiDataType_Float, &fbm_amplitude_persistence[1], &step);
      ImGui::InputScalar("Frequency##fbm", ImGuiDataType_Float, &fbm_frequency_lacunarity[0], &step);
      ImGui::SameLine();
      ImGui::InputScalar("Lacunarity##fbm", ImGuiDataType_Float, &fbm_frequency_lacunarity[1], &step);
      ImGui::PopItemWidth();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Billow")) {
      ImGui::SliderInt("Octaves##billow", &billow_octaves, 1.0f, 8.0f);
      ImGui::PushItemWidth(120);
      ImGui::InputScalar("Amplitude##billow", ImGuiDataType_Float, &billow_amplitude_persistence[0], &step);
      ImGui::SameLine();
      ImGui::InputScalar("Persistency##billow", ImGuiDataType_Float, &billow_amplitude_persistence[1], &step);
      ImGui::InputScalar("Frequency##billow", ImGuiDataType_Float, &billow_frequency_lacunarity[0], &step);
      ImGui::SameLine();
      ImGui::InputScalar("Lacunarity##billow", ImGuiDataType_Float, &billow_frequency_lacunarity[1], &step);
      ImGui::PopItemWidth();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Ridged Multi")) {
      ImGui::SliderInt("Octaves##rmf", &rmf_octaves, 1.0f, 8.0f);
      ImGui::PushItemWidth(120);
      ImGui::InputScalar("Amplitude##rmf", ImGuiDataType_Float, &rmf_amplitude_persistence[0], &step);
      ImGui::SameLine();
      ImGui::InputScalar("Persistency##rmf", ImGuiDataType_Float, &rmf_amplitude_persistence[1], &step);
      ImGui::InputScalar("Frequency##rmf", ImGuiDataType_Float, &rmf_frequency_lacunarity[0], &step);
      ImGui::SameLine();
      ImGui::InputScalar("Lacunarity##rmf", ImGuiDataType_Float, &rmf_frequency_lacunarity[1], &step);
      ImGui::InputScalar("H##rmf", ImGuiDataType_Float, &rmf_h_offset[0], &step);
      ImGui::SameLine();
      ImGui::InputScalar("Offset##rmf", ImGuiDataType_Float, &rmf_h_offset[1], &step);
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
