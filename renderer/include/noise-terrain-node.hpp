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
class NoiseTerrainNode : public Node {
public:
  explicit NoiseTerrainNode() noexcept;

  void render_offscreen(const int width, const int height) override;

  void set_render_state(const int width, const int height) override;

public:
  bool dirty = true;
};
} // namespace scene
} // namespace odo

#endif // NOISETERRAINNODE_HPP
