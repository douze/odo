#ifndef TERRAIN_H
#define TERRAIN_H

#include "mesh.hpp"

namespace odo::mesh {

struct TerrainVertex {
  float x, y;
  float r, g, b;
  float u, v;
};

/**
 * @brief 3D terrain using patches.
 */
class Terrain : public Mesh {
public:
  /**
   * @brief Create a terrain.
   */
  explicit Terrain() noexcept;

  /**
   * @copydoc
   * @note Generate the noise texture.
   */
  void prepare() override;

  void render() const override;

  void render_ui() const override;

private:
  /** Noise texture */
  GLuint texture;
};

} // namespace odo::mesh

#endif // TERRAIN_H
