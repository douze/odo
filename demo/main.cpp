#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "spdlog/spdlog.h"
#include "terrain.hpp"
#include "terrainmaterial.hpp"
#include "transformation.hpp"
#include "triangle.hpp"
#include "vertexcolormaterial.hpp"

#include <iostream>
#include <string>

using namespace renderer;

int main() {
  spdlog::set_level(spdlog::level::debug);

  const int width = 1280;
  const int height = 800;

  Renderer renderer{width, height};

  // Do I really need shared_ptr ? For the update loop ?
  std::shared_ptr<mesh::Triangle> triangle{std::make_shared<mesh::Triangle>()};
  std::shared_ptr<material::VertexColorMaterial> vertexcolormaterial{
      std::make_shared<material::VertexColorMaterial>()};

  std::shared_ptr<mesh::Terrain> terrain{std::make_shared<mesh::Terrain>()};
  std::shared_ptr<material::TerrainMaterial> terrainMaterial{
      std::make_shared<material::TerrainMaterial>()};
  scene::Node triangleNode{triangle,
                           mesh::Transformation{glm::vec3{0.0f, 0.0f, -2.0f}},
                           vertexcolormaterial};
  renderer.getScene().getRoot().addChild(triangleNode);

  scene::Node terrainNode{terrain,
                          mesh::Transformation{glm::vec3{0.0f, 0.0f, -2.0f}},
                          terrainMaterial};
  renderer.getScene().getRoot().addChild(terrainNode);

  scene::Camera camera{glm::vec3{0.0f, 0.0f, 0.0f},
                       width / static_cast<float>(height)};

  renderer.getScene().setCamera(std::make_shared<scene::Camera>(camera));

  return renderer.run();
}

