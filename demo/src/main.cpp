#include "camera.hpp"
#include "full-screen-quad.hpp"
#include "noise-terrain-material.hpp"
#include "noise-terrain-node.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "spdlog/spdlog.h"
#include "terrain-material.hpp"
#include "terrain-node.hpp"
#include "terrain.hpp"
#include "transformation.hpp"
#include "vertex-color-material.hpp"

struct Configuration {
  int width;
  int height;
};

int main() {
  using namespace odo;

  // Configuration
  spdlog::set_level(spdlog::level::debug);
  Configuration configuration{1280, 800};

  // Create renderer
  Renderer renderer{configuration.width, configuration.height};
  scene::Scene& scene{renderer.get_scene()};
  scene::Node& root{scene.get_root()};

  // Setup scene
  scene::NoiseTerrainNode noiseTerrainNode;
  scene::TerrainNode terrainNode;
  noiseTerrainNode.add_child(terrainNode);
  root.add_child(noiseTerrainNode);

  // Assign main camera
  scene::Camera camera{glm::vec3{1.0f, 3.0f, 3.0f}, glm::vec2{-90.0f, -45.0f},
                       configuration.width / static_cast<float>(configuration.height)};
  scene.attach_main_camera(std::make_shared<scene::Camera>(camera));

  // Run loop
  renderer.prepare();
  return renderer.run();
}
