#ifndef NOISETERRAINMATERIAL_H
#define NOISETERRAINMATERIAL_H

#include "material.hpp"

namespace renderer {
namespace material {

/**
 * @brief Material used to generate terrain texture with noise.
 */
class NoiseTerrainMaterial : public Material {
public:
  explicit NoiseTerrainMaterial() noexcept;
};

} // namespace material
} // namespace renderer

#endif // NOISETERRAINMATERIAL_H
