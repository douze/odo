#include "scene.hpp"
#include <memory>

using namespace odo::scene;
using namespace odo::mesh;

Node::Node(mesh::Transformation transformation) noexcept : Node{nullptr, nullptr, transformation} {}

Node::Node(std::unique_ptr<mesh::Mesh> mesh, std::unique_ptr<material::Material> material,
           mesh::Transformation transformation) noexcept
    : mesh{std::move(mesh)}, material{std::move(material)}, transformation{transformation} {}

void Node::add_child(Node& child) { children.push_back(child); }

Scene::Scene() noexcept : root{Node{Transformation{glm::vec3{0.f, 0.f, 0.f}}}} {}
