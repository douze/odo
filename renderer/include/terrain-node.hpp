#ifndef TERRAINNODE_HPP
#define TERRAINNODE_HPP

#include "gui-provider.hpp"
#include "scene.hpp"

namespace odo {

namespace mesh {
class Terrain;
}

namespace material {
class TerrainMaterial;
}

namespace scene {

/**
 * @brief Specification of Node used for the terrain.
 */
class TerrainNode : public Node, public odo::GuiProvider {

public:
  explicit TerrainNode(const std::string& name, std::unique_ptr<mesh::Mesh> mesh,
                       std::unique_ptr<material::Material> material, mesh::Transformation transformation) noexcept;

  void render_ui() override;

private:
  /**
   * @brief Build the list of possible grid sizes.
   * @note Max value is hardcoded in this function.
   */
  void build_grid_size_list();

  /**
   * @brief Update the node properties, by senting them to the mesh & material.
   */
  void update_node_properties();

  /**
   * @return the terrain mesh.
   */
  mesh::Terrain* get_terrain_mesh() const;

  /**
   * @return the terrain material.
   */
  material::TerrainMaterial* get_terrain_material() const;

private:
  /** The default index of the selection of grid size. Indexed from 0. */
  int grid_size_selection_index = 2;

  /** List of possible grid sizes */
  std::vector<std::string> grid_size_list;
};

} // namespace scene
} // namespace odo

#endif // TERRAINNODE_HPP
