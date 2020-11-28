#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "material.hpp"

namespace odo::material {

/**
 * @brief Material used for the terrain (using precomputed noise heightmap).
 */
class TerrainMaterial : public Material {
public:
  explicit TerrainMaterial() noexcept;
};

} // namespace odo::material

#endif // TERRAINMATERIAL_H
