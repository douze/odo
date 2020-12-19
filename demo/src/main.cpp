#include "camera.hpp"
#include "full-screen-quad.hpp"
#include "noise-terrain-material.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "spdlog/spdlog.h"
#include "terrain-material.hpp"
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

  // Add full screen quad for noise
  scene::Node noiseTerrainNode{"Material: Noise Terrain",
                               std::make_unique<mesh::FullScreenQuad>(mesh::FullScreenQuad{}),
                               std::make_unique<material::NoiseTerrainMaterial>(material::NoiseTerrainMaterial{}),
                               mesh::Transformation{glm::vec3{0.0f}}, true};

  // Add terrain
  scene::Node terrainNode{"Mesh: Terrain", std::make_unique<mesh::Terrain>(mesh::Terrain{}),
                          std::make_unique<material::TerrainMaterial>(material::TerrainMaterial{}),
                          mesh::Transformation{glm::vec3{0.0f}, glm::vec3{-90.0f, 0.0f, 0.0f}, glm::vec3{2.0f}}};
  noiseTerrainNode.add_child(terrainNode);

  root.add_child(noiseTerrainNode);

  // Assign main camera
  scene::Camera camera{glm::vec3{0.0f, 1.0f, 4.0f}, configuration.width / static_cast<float>(configuration.height)};
  scene.attach_main_camera(std::make_shared<scene::Camera>(camera));

  // Run loop
  renderer.prerun();
  return renderer.run();
}
