#include "terrain-node.hpp"
#include "terrain-material.hpp"
#include "terrain.hpp"
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <string>

using namespace odo::scene;

TerrainNode::TerrainNode(const std::string& name, std::unique_ptr<mesh::Mesh> mesh,
                         std::unique_ptr<material::Material> material, mesh::Transformation transformation) noexcept
    : Node{name, std::move(mesh), std::move(material), transformation} {
  build_grid_size_list();
  update_node_properties();
}

void TerrainNode::build_grid_size_list() {
  const int max_size = 5;
  for (int i = 0; i < max_size; i++) {
    const std::string size = std::to_string(i + 1);
    grid_size_list.push_back(size + "x" + size);
  }
}

void TerrainNode::update_node_properties() {
  const int grid_size = grid_size_selection_index + 1; // 0 indexed
  get_terrain_mesh()->instance_count = grid_size * grid_size;
  get_terrain_material()->grid_size = grid_size;
  get_terrain_material()->patch_size = get_terrain_mesh()->get_patch_size();
}

odo::mesh::Terrain* TerrainNode::get_terrain_mesh() const { return dynamic_cast<odo::mesh::Terrain*>(get_mesh_ptr()); }

odo::material::TerrainMaterial* TerrainNode::get_terrain_material() const {
  return dynamic_cast<odo::material::TerrainMaterial*>(get_material_ptr());
}

void TerrainNode::render_ui() {
  if (ImGui::CollapsingHeader("Node: Terrain")) {
    ImGui::Combo(
        "Size", &grid_size_selection_index,
        [](void* data, int idx, const char** out_text) {
          std::vector<std::string> from_data = *static_cast<std::vector<std::string>*>(data);
          *out_text = from_data[idx].c_str();
          return true;
        },
        static_cast<void*>(&grid_size_list), grid_size_list.size());
    get_terrain_material()->render_ui();
    get_terrain_mesh()->render_ui();
    update_node_properties();
  }
}
