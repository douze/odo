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

  /**
   * @return the offscreen texture
   */
  GLuint get_offscreen_texture() const { return texture; }

  /**
   * @return the offscreen fbo
   */
  GLuint get_offscreen_fbo() const { return fbo; }

  void render_ui() override;

  void set_uniforms() const override;

  void prepare(const int width, const int height) override;

private:
  GLuint fbo;
  GLuint texture;

  bool use_demo_value = true;
  int noise_function = 3;

  int fbm_octaves = 6;
  float fbm_amplitude_persistence[2] = {1.0f, 0.5f};
  float fbm_frequency_lacunarity[2] = {1.0f, 2.0f};

  int billow_octaves = 6;
  float billow_amplitude_persistence[2] = {1.0f, 0.5f};
  float billow_frequency_lacunarity[2] = {1.0f, 2.0f};

  int rmf_octaves = 6;
  float rmf_amplitude_persistence[2] = {1.0f, 2.0f};
  float rmf_frequency_lacunarity[2] = {1.0f, 2.0f};
  float rmf_h_offset[2] = {1.0f, 1.0f};
};

} // namespace odo::material

#endif // NOISETERRAINMATERIAL_H
