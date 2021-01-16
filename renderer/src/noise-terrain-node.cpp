#include "noise-terrain-node.hpp"
#include "full-screen-quad.hpp"
#include "noise-terrain-material.hpp"

using namespace odo::scene;

NoiseTerrainNode::NoiseTerrainNode() noexcept
    : Node{"Material: Noise Terrain", std::make_unique<mesh::FullScreenQuad>(mesh::FullScreenQuad{}),
           std::make_unique<material::NoiseTerrainMaterial>(material::NoiseTerrainMaterial{}),
           mesh::Transformation{glm::vec3{0.0f}}, true} {}

void NoiseTerrainNode::set_render_state(const int width, const int height) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glBindFramebuffer(GL_FRAMEBUFFER, get_material().get_offscreen_fbo());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NoiseTerrainNode::render_offscreen(const int width, const int height) {
  if (dirty) {
    dirty = false;

    set_render_state(width, height);

    get_material_ptr()->use();
    get_material_ptr()->set_uniforms();
    get_mesh_ptr()->render();
  }
}
