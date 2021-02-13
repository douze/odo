#include "noise-terrain-node.hpp"
#include "full-screen-quad.hpp"
#include "noise-terrain-material.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace odo::scene;

NoiseTerrainNode::NoiseTerrainNode() noexcept
    : Node{"Noise Terrain", std::make_unique<mesh::FullScreenQuad>(mesh::FullScreenQuad{}),
           std::make_unique<material::NoiseTerrainMaterial>(material::NoiseTerrainMaterial{}),
           mesh::Transformation{glm::vec3{0.0f}}} {}

void NoiseTerrainNode::set_render_state(const int width, const int height) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glViewport(0, 0, 1024, 1024);
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glBindFramebuffer(GL_FRAMEBUFFER, get_noise_terrain_material().get_offscreen_fbo());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int saveScreenshot(const char* filename) {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  int x = viewport[0];
  int y = viewport[1];
  int width = viewport[2];
  int height = viewport[3];

  char* data = (char*)malloc((size_t)(width * height * 3)); // 3 components (R, G, B)

  if (!data)
    return 0;

  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

  int saved = stbi_write_png(filename, width, height, 3, data, 0);

  free(data);

  return saved;
}

int once = false;

int NoiseTerrainNode::render(const Camera& camera, std::optional<std::reference_wrapper<scene::Node>> parent) {
  if (get_noise_terrain_material().is_dirty()) {
    get_noise_terrain_material().set_dirty(false);

    set_render_state(camera.get_window_width(), camera.get_window_height());

    get_material().use();
    get_material().set_uniforms();
    get_mesh().render();
    if (once) {
      once = false;
      stbi_flip_vertically_on_write(1);
      saveScreenshot("yolo.png");
    }
    return true;
  }
  return false;
}

odo::material::NoiseTerrainMaterial& NoiseTerrainNode::get_noise_terrain_material() const {
  return dynamic_cast<odo::material::NoiseTerrainMaterial&>(get_material());
}
