#include "scene.hpp"

using namespace renderer::scene;
using namespace renderer::mesh;

Node::Node(mesh::Transformation transformation) noexcept
    : Node{nullptr, transformation, nullptr} {}

Node::Node(const std::shared_ptr<mesh::Mesh>& mesh,
           mesh::Transformation transformation,
           const std::shared_ptr<material::Material>& material
          ) noexcept
    : mesh{mesh}, transformation{transformation}, material{material} {}

void Node::addChild(Node& child) { children.push_back(child); }

Scene::Scene() noexcept
    : root{Node{Transformation{glm::vec3{0.f, 0.f, 0.f}}}} {}
