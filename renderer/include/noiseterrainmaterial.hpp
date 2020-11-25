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
};

} // namespace odo::material

#endif // NOISETERRAINMATERIAL_H
