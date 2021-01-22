#ifndef NOISETERRAINNODE_HPP
#define NOISETERRAINNODE_HPP

#include "scene.hpp"

namespace odo {

namespace mesh {
class FullScreenQuad;
}

namespace material {
class NoiseTerrainMaterial;
}

namespace scene {
/**
 * @brief Specification of Node used for the terrain noise.
 */
class NoiseTerrainNode : public Node {
public:
  explicit NoiseTerrainNode() noexcept;

  /**
   * @return true because we affected the render state when rendering this node.
   */
  bool should_restore_render_state() const override { return true; }

  /**
   * @return the terrain noise material.
   */
  material::NoiseTerrainMaterial& get_noise_terrain_material() const;

  int render(const Camera& camera, std::optional<std::reference_wrapper<scene::Node>> parent) override;

  void set_render_state(const int width, const int height) override;

public:
  bool dirty = true;
};
} // namespace scene
} // namespace odo

#endif // NOISETERRAINNODE_HPP
