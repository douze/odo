#include "terrain-node.hpp"
#include "terrain.hpp"
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <string>

using namespace odo::scene;

TerrainNode::TerrainNode(const std::string& name, std::unique_ptr<mesh::Mesh> mesh,
                         std::unique_ptr<material::Material> material, mesh::Transformation transformation)
    : Node{name, std::move(mesh), std::move(material), transformation} {
  build_grid_size_list();
}

void TerrainNode::build_grid_size_list() {
  const int max_size = 5;
  for (int i = 0; i < max_size; i++) {
    const std::string size = std::to_string(i + 1);
    grid_size_list.push_back(size + "x" + size);
  }
}

void TerrainNode::render_ui() {
  if (ImGui::CollapsingHeader("Node: Terrain")) {
    ImGui::Combo(
        "Size", &grid_size,
        [](void* data, int idx, const char** out_text) {
          std::vector<std::string> from_data = *static_cast<std::vector<std::string>*>(data);
          *out_text = from_data[idx].c_str();
          return true;
        },
        static_cast<void*>(&grid_size_list), grid_size_list.size());
    get_material().render_ui();
    // get_mesh().render_ui();

    odo::mesh::Terrain* t = dynamic_cast<odo::mesh::Terrain*>(get_mesh_ptr());
    t->instance_count = grid_size + 1;
  }
}
