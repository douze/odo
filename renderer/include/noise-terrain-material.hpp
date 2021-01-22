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

  bool is_dirty() const { return dirty; }
  void set_dirty(bool dirty) { this->dirty = dirty; }

private:
  void add_combo(const char* label, int* current_item, const char* items_separated_by_zeros);
  void add_checkbox(const char* label, bool* v);
  void add_input_scalar(const char* label, void* p_data, const void* p_step);
  void add_slider_int(const char* label, int* v, int v_min, int v_max);

private:
  GLuint fbo;
  GLuint texture;

  bool dirty = true;

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
