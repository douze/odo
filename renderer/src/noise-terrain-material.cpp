#include "noise-terrain-material.hpp"
#include <imgui.h>

using namespace odo::material;

NoiseTerrainMaterial::NoiseTerrainMaterial() noexcept : Material{"noise-terrain.vs.glsl", "noise-terrain.fs.glsl"} {}

void NoiseTerrainMaterial::prepare_offscreen() {
  // FBO
  glCreateFramebuffers(1, &fbo);

  // Texture
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glTextureStorage2D(texture, 1, GL_RGB8, 800, 600);
  glTextureSubImage2D(texture, 0, 0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, 0);
  //   glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //   glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, texture, 0);
}

void NoiseTerrainMaterial::render_ui() {
  ImGui::SliderInt("Octaves", &octaves, 1.0f, 8.0f);
  ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 2.0f);
  ImGui::SliderFloat("Frequency", &frequency, 0.0f, 12.0f);
  ImGui::Text("Noise texture");
  ImGui::Image((void*)(intptr_t)texture, ImVec2(400, 400), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}

void NoiseTerrainMaterial::set_uniforms() const {
  glProgramUniform1i(fs, 0, octaves);
  glProgramUniform1f(fs, 1, amplitude);
  glProgramUniform1f(fs, 2, frequency);
}
