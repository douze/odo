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

  Renderer renderer{640, 480};

  scene::Node triangleNode{std::make_shared<mesh::Triangle>(),
                           mesh::Transformation{glm::vec3{0.5f, 0.5f, -2.0f}},
                           std::make_shared<material::VertexColorMaterial>()};
  renderer.getScene().getRoot().addChild(triangleNode);

  scene::Camera camera{glm::vec3{0.0f, 0.0f, 0.0f}, 640, 480};
  renderer.getScene().setCamera(std::make_shared<scene::Camera>(camera));

  return renderer.run();
}
