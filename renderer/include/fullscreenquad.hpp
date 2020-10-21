#ifndef FULLSCREENQUAD_H
#define FULLSCREENQUAD_H

#include "mesh.hpp"
#include <glad/glad.h>

namespace renderer {
namespace mesh {

struct FullScreenQuadVertex {
  float x, y;
  float u, v;
};

/**
 * @brief Full screen quad, mainly used for offscreen rendering.
 */
class FullScreenQuad : public Mesh {
public:
  /**
   * @brief Create a full screen quad for offscreen rendering.
   */
  explicit FullScreenQuad() noexcept;

  void render() const override;
};

} // namespace mesh
} // namespace renderer

#endif // FULLSCREENQUAD_H
