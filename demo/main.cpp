#include "renderer.hpp"
#include "scene.hpp"
#include "triangle.hpp"

using namespace renderer;

int main() {
  Renderer renderer{640, 480};
  
  scene::Scene scene;
  scene::Node triangleNode{std::make_shared<mesh::Triangle>()};
  renderer.scene.getRoot()->addChild(triangleNode);
  
  return renderer.run();
}
