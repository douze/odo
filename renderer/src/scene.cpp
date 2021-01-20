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

void Node::prepare(const int width, const int height) {
  if (is_renderable()) {
    mesh->prepare();
    material->prepare(width, height);
  }
}

void Node::render_ui() {
  if (is_renderable()) {
    if (has_name() && ImGui::CollapsingHeader(get_name().c_str())) {
      mesh->render_ui();
      material->render_ui();
    }
  }
}

int Node::render(const Camera& camera, std::optional<std::reference_wrapper<scene::Node>> parent) {
  material->use();
  material->set_transformation_matrix(get_transformation());
  material->set_camera_matrices(camera);
  material->set_uniforms();
  if (parent.has_value()) {
    material->set_uniforms_from_parent(parent.value().get().get_material());
  }
  mesh->render();
  return true;
}

Scene::Scene() noexcept : root{Node{Transformation{glm::vec3{0.f, 0.f, 0.f}}}} {}

void Scene::render_ui(Node& node) {
  node.render_ui();

  for (scene::Node& child : node.get_children()) {
    render_ui(child);
  }
}
