#include "terrain.hpp"
#include "full-screen-quad.hpp"
#include "noise-terrain-material.hpp"
#include <imgui.h>

using namespace odo::mesh;

Terrain::Terrain() noexcept {
  const float size = 1.0f;
  const TerrainVertex vertices[4] = {{0.0f, 0.0f, 1.f, 0.f, 0.f, 0.0f, 0.0f},
                                     {size, 0.0f, 0.f, 1.f, 0.f, 1.0f, 0.0f},
                                     {size, size, 0.f, 0.f, 1.f, 1.0f, 1.0f},
                                     {0.0f, size, 1.f, 1.f, 1.f, 0.0f, 1.0f}};

  GLuint vbo;
  glCreateBuffers(1, &vbo);
  glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &vao);

  glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(TerrainVertex));

  glEnableVertexArrayAttrib(vao, 0);
  glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 0, 0);

  glEnableVertexArrayAttrib(vao, 1);
  glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 2));
  glVertexArrayAttribBinding(vao, 1, 0);

  glEnableVertexArrayAttrib(vao, 2);
  glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, (sizeof(float) * 5));
  glVertexArrayAttribBinding(vao, 2, 0);
}

void Terrain::render() const {
  glBindVertexArray(vao);
  glPatchParameteri(GL_PATCH_VERTICES, 4);
  glDrawArraysInstanced(GL_PATCHES, 0, 4, instance_count);
}
