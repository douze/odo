#include "scene.hpp"
#include <memory>

using namespace odo::scene;
using namespace odo::mesh;

Node::Node(mesh::Transformation transformation) noexcept
    : mesh{nullptr}, material{nullptr}, transformation{transformation} {}

Node::Node(std::unique_ptr<mesh::Mesh> mesh,
           mesh::Transformation transformation,
           std::unique_ptr<material::Material> material) noexcept
    : mesh{std::move(mesh)}, material{std::move(material)},
      transformation{transformation} {}

void Node::addChild(Node& child) { children.push_back(child); }

Scene::Scene() noexcept
    : root{Node{Transformation{glm::vec3{0.f, 0.f, 0.f}}}} {}
