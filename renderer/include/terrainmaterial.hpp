#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "material.hpp"

namespace renderer {
namespace material {

class TerrainMaterial : public Material {
public:
  explicit TerrainMaterial() noexcept;
};

} // namespace material
} // namespace renderer

#endif // TERRAINMATERIAL_H
