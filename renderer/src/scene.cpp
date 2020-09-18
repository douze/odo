#include "scene.hpp"

using namespace renderer::scene;
using namespace renderer::mesh;

Node::Node() : mesh{nullptr} {}
Node::Node(std::shared_ptr<mesh::Mesh> mesh) : mesh{mesh} {}

void Node::addChild(Node& child) { children.push_back(child); }

Scene::Scene() : root{std::make_unique<Node>()} {}
