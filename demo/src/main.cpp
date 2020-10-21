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

#include <iostream>
#include <string>

using namespace renderer;
#include <iostream>
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

  std::shared_ptr<mesh::FullScreenQuad> fsq{
      std::make_shared<mesh::FullScreenQuad>()};
  std::shared_ptr<material::NoiseTerrainMaterial> noiseTerrainMaterial{
      std::make_shared<material::NoiseTerrainMaterial>()};

  scene::Node triangleNode{triangle,
                           mesh::Transformation{glm::vec3{0.0f, 0.0f, -2.0f}},
                           vertexcolormaterial};
  renderer.getScene().getRoot().addChild(triangleNode);

  scene::Node terrainNode{terrain,
                          mesh::Transformation{glm::vec3{0.0f, 0.0f, -4.0f}},
                          terrainMaterial};
  renderer.getScene().getRoot().addChild(terrainNode);

//   scene::Node fsqNode{fsq,
//                           mesh::Transformation{glm::vec3{0.0f, 0.0f, -2.0f}},
//                           noiseTerrainMaterial};
//   renderer.getScene().getRoot().addChild(fsqNode);

  scene::Camera camera{glm::vec3{0.0f, 0.0f, 0.0f},
                       width / static_cast<float>(height)};

  renderer.getScene().setCamera(std::make_shared<scene::Camera>(camera));

  renderer.prerun();

  return renderer.run();
}
