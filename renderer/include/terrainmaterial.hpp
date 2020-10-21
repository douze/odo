#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "material.hpp"

namespace renderer {
namespace material {

/**
 * @brief Material used for the terrain (using precomputed noise heightmap).
 */
class TerrainMaterial : public Material {
public:
  explicit TerrainMaterial() noexcept;
};

} // namespace material
} // namespace renderer

#endif // TERRAINMATERIAL_H
