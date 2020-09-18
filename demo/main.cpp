#include "renderer.hpp"
#include "scene.hpp"
#include "triangle.hpp"
#include "spdlog/spdlog.h"

using namespace renderer;

int main() {
    spdlog::set_level(spdlog::level::debug);

    Renderer renderer{640, 480};

    scene::Scene scene;
    scene::Node triangleNode{std::make_shared<mesh::Triangle>()};
    renderer.scene.getRoot()->addChild(triangleNode);

    return renderer.run();
}
