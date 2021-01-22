#include "noise-terrain-node.hpp"
#include "full-screen-quad.hpp"
#include "noise-terrain-material.hpp"

using namespace odo::scene;

NoiseTerrainNode::NoiseTerrainNode() noexcept
    : Node{"Material: Noise Terrain", std::make_unique<mesh::FullScreenQuad>(mesh::FullScreenQuad{}),
           std::make_unique<material::NoiseTerrainMaterial>(material::NoiseTerrainMaterial{}),
           mesh::Transformation{glm::vec3{0.0f}}} {}

void NoiseTerrainNode::set_render_state(const int width, const int height) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glBindFramebuffer(GL_FRAMEBUFFER, get_noise_terrain_material().get_offscreen_fbo());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int NoiseTerrainNode::render(const Camera& camera, std::optional<std::reference_wrapper<scene::Node>> parent) {
  if (get_noise_terrain_material().is_dirty()) {
    get_noise_terrain_material().set_dirty(false);

    set_render_state(camera.get_window_width(), camera.get_window_height());

    get_material().use();
    get_material().set_uniforms();
    get_mesh().render();
    return true;
  }
  return false;
}

odo::material::NoiseTerrainMaterial& NoiseTerrainNode::get_noise_terrain_material() const {
  return dynamic_cast<odo::material::NoiseTerrainMaterial&>(get_material());
}
