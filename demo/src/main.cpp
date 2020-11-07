#include "camera.hpp"
#include "fullscreenquad.hpp"
#include "noiseterrainmaterial.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "spdlog/spdlog.h"
#include "terrain.hpp"
#include "terrainmaterial.hpp"
#include "transformation.hpp"
#include "triangle.hpp"
#include "vertexcolormaterial.hpp"

struct Configuration {
  int width;
  int height;
};

int main() {
  using namespace renderer;

  // Configuration
  spdlog::set_level(spdlog::level::debug);
  Configuration configuration{1280, 800};

  // Create renderer
  Renderer renderer{configuration.width, configuration.height};
  scene::Scene& scene{renderer.getScene()};
  scene::Node& root{scene.getRoot()};

  // Add test triangle
  scene::Node triangleNode{std::make_unique<mesh::Triangle>(mesh::Triangle{}),
                           mesh::Transformation{glm::vec3{0.0f, 0.0f, -2.0f}},
                           std::make_unique<material::VertexColorMaterial>(
                               material::VertexColorMaterial{})};
  root.addChild(triangleNode);

  // Add terrain
  scene::Node terrainNode{
      std::make_unique<mesh::Terrain>(mesh::Terrain{}),
      mesh::Transformation{glm::vec3{0.0f, 0.0f, -4.0f}},
      std::make_unique<material::TerrainMaterial>(material::TerrainMaterial{})};
  root.addChild(terrainNode);

  // Assign main camera
  scene::Camera camera{glm::vec3{0.0f, 0.0f, 0.0f},
                       configuration.width /
                           static_cast<float>(configuration.height)};
  scene.setCamera(std::make_shared<scene::Camera>(camera));

  // Run loop
  renderer.prerun();
  return renderer.run();
}
