#ifndef NOISETERRAINMATERIAL_H
#define NOISETERRAINMATERIAL_H

#include "material.hpp"

namespace odo::material {

/**
 * @brief Material used to generate terrain texture with noise.
 */
class NoiseTerrainMaterial : public Material {
public:
  explicit NoiseTerrainMaterial() noexcept;

  void render_ui() override;

  void set_uniforms() const override;

  void prepare_offscreen() override;

  GLuint get_offscreen_texture() const override { return texture; }

  GLuint get_offscreen_fbo() const override { return fbo; }

private:
  GLuint fbo;
  GLuint texture;

  int octaves = 6;
  float amplitude = 0.5f;
  float frequency = 3.0f;
};

} // namespace odo::material

#endif // NOISETERRAINMATERIAL_H
