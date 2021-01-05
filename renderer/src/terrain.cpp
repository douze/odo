#include "terrain.hpp"
#include "full-screen-quad.hpp"
#include "noise-terrain-material.hpp"
#include <imgui.h>

using namespace odo::mesh;

Terrain::Terrain() noexcept {
  const float size = patch_size;
  const TerrainVertex vertices[4] = {{0.0f, 0.0f}, {size, 0.0f}, {size, size}, {0.0f, size}};

  GLuint vbo;
  glCreateBuffers(1, &vbo);
  glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &vao);

  glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(TerrainVertex));

  glEnableVertexArrayAttrib(vao, 0);
  glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 0, 0);
}

void Terrain::render() const {
  glBindVertexArray(vao);
  glPatchParameteri(GL_PATCH_VERTICES, 4);
  glDrawArraysInstanced(GL_PATCHES, 0, 4, instance_count);
}
