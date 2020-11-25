#include "fullscreenquad.hpp"

using namespace odo::mesh;

FullScreenQuad::FullScreenQuad() noexcept {

  const FullScreenQuadVertex vertices[6] = {
      {-1.0f, -1.0f, 0.0f, 0.0f}, {1.0f, -1.0f, 1.0f, 0.0f},
      {-1.0f, 1.0f, 0.0f, 1.0f},  {-1.0f, 1.0f, 0.0f, 1.0f},
      {1.0f, -1.0f, 1.0f, 0.0f},  {1.0f, 1.0f, 1.0f, 1.0f}};

  GLuint vbo;
  glCreateBuffers(1, &vbo);
  glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &vao);

  glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(FullScreenQuadVertex));

  glEnableVertexArrayAttrib(vao, 0);
  glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 0, 0);

  glEnableVertexArrayAttrib(vao, 1);
  glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, (sizeof(float) * 2));
  glVertexArrayAttribBinding(vao, 1, 0);
}

void FullScreenQuad::render() const {
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
