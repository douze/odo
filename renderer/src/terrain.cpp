#include "terrain.hpp"
#include "fullscreenquad.hpp"
#include "noiseterrainmaterial.hpp"

using namespace renderer::mesh;
#include <iostream>
Terrain::Terrain() noexcept {
  const TerrainVertex vertices[4] = {{-1.0f, -1.0f, 1.f, 0.f, 0.f, 0.0f, 0.0f},
                                     {-1.0f, 1.0f, 0.f, 1.f, 0.f, 0.0f, 1.0f},
                                     {1.0f, 1.0f, 0.f, 0.f, 1.f, 1.0f, 1.0f},
                                     {1.0f, -1.0f, 1.f, 1.f, 1.f, 1.0f, 0.0f}};

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

#include <iostream>

void Terrain::prepare() {
  std::cout << "smg to do" << std::endl;

  // Full screen quad
  FullScreenQuad fsq;
  material::NoiseTerrainMaterial noiseTerrainMaterial;
  
  // FBO
  GLuint fbo;
  glCreateFramebuffers(1, &fbo);

  // Texture
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glTextureStorage2D(texture, 1, GL_RGB8, 800, 600);
  glTextureSubImage2D(texture, 0, 0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, 0);
//   glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, texture, 0);

  if (glCheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER) !=
      GL_FRAMEBUFFER_COMPLETE)
    std::cerr << "framebuffer error\n";
  else
    std::cout << "ok\n";

  // Draw
  glViewport(0,0,800,600);
  glBindTexture(GL_TEXTURE_2D, texture);
  glActiveTexture(GL_TEXTURE0);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  noiseTerrainMaterial.use();
  fsq.render();
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Terrain::render() const {
  glBindTextureUnit(0, texture);

  glBindVertexArray(vao);
  glPatchParameteri(GL_PATCH_VERTICES, 4);
  glDrawArrays(GL_PATCHES, 0, 4);
}
