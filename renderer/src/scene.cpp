#include "scene.hpp"
#include <imgui.h>

using namespace odo::scene;
using namespace odo::mesh;

Node::Node(mesh::Transformation transformation) noexcept
    : name{std::nullopt}, mesh{nullptr}, material{nullptr}, transformation{transformation} {}

Node::Node(const std::string& name, std::unique_ptr<mesh::Mesh> mesh, std::unique_ptr<material::Material> material,
           mesh::Transformation transformation) noexcept
    : name{std::make_optional<std::string>(name)},
      mesh{std::move(mesh)},
      material{std::move(material)},
      transformation{transformation} {}

void Node::add_child(Node& child) { children.push_back(child); }

Scene::Scene() noexcept : root{Node{Transformation{glm::vec3{0.f, 0.f, 0.f}}}} {}

void Scene::render_ui(scene::Node& node) {
  if (node.is_renderable()) {
    if (node.has_name() && ImGui::CollapsingHeader(node.get_name().c_str())) {
      node.get_mesh().render_ui();
      node.get_material().render_ui();
    }
    // Do i need a case without collapsing header ?
  }
  for (scene::Node& child : node.get_children()) {
    render_ui(child);
  }
}
