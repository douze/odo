#include "camera.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "spdlog/spdlog.h"
#include "transformation.hpp"
#include "triangle.hpp"
#include "vertexcolormaterial.hpp"

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

  scene::Node triangleNode{triangle,
                           mesh::Transformation{glm::vec3{0.0f, 0.0f, -2.0f}},
                           vertexcolormaterial};
  renderer.getScene().getRoot().addChild(triangleNode);

  scene::Camera camera{glm::vec3{0.0f, 0.0f, 0.0f}, width, height};
  renderer.getScene().setCamera(std::make_shared<scene::Camera>(camera));

  return renderer.run();
}
