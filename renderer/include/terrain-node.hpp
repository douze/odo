#ifndef TERRAINNODE_HPP
#define TERRAINNODE_HPP

#include "gui-provider.hpp"
#include "scene.hpp"

namespace odo::scene {

class TerrainNode : public Node, public odo::GuiProvider {

public:
  TerrainNode(const std::string& name, std::unique_ptr<mesh::Mesh> mesh, std::unique_ptr<material::Material> material,
              mesh::Transformation transformation);

  void render_ui() override;

private:
  void build_grid_size_list();

private:
  int grid_size = 0;
  std::vector<std::string> grid_size_list;
};

} // namespace odo::scene

#endif // TERRAINNODE_HPP
