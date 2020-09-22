#include "triangle.hpp"
#include "vertexcolormaterial.hpp"

using namespace renderer::mesh;

Triangle::Triangle() noexcept {
  const vertex_t vertices[3] = {{-0.6f, -0.4f, 0.f, 1.f, 0.f, 0.f},
                                {0.6f, -0.4f, 0.f, 0.f, 1.f, 0.f},
                                {0.f, 0.6f, 0.f, 0.f, 0.f, 1.f}};

  GLuint vbo;
  glCreateBuffers(1, &vbo);
  glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &vao);

  glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(vertex_t));

  glEnableVertexArrayAttrib(vao, 0);
  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 0, 0);

  glEnableVertexArrayAttrib(vao, 1);
  glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 3));
  glVertexArrayAttribBinding(vao, 1, 0);
}

void Triangle::render() const {
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
