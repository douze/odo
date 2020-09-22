#include "renderer.hpp"
#include "scene.hpp"
#include "triangle.hpp"
#include "spdlog/spdlog.h"
#include "transformation.hpp"
#include "vertexcolormaterial.hpp"

using namespace renderer;

int main() {
    spdlog::set_level(spdlog::level::debug);

    Renderer renderer{640, 480};

    scene::Node triangleNode{std::make_shared<mesh::Triangle>(), mesh::Transformation{glm::vec3{0.5f, 0.5f, 0.f}}, std::make_shared<material::VertexColorMaterial>()};
    renderer.scene.getRoot()->addChild(triangleNode);

    return renderer.run();
}
