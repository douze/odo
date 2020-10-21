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

class FullScreenQuad : public Mesh {
public:
  explicit FullScreenQuad() noexcept;

//   void prepare() const override;
  void render() const override;

private:
  GLuint vao;
  GLuint program;
};

} // namespace mesh
} // namespace renderer

#endif // FULLSCREENQUAD_H
