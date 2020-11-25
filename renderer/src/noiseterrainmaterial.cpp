#include "noiseterrainmaterial.hpp"

using namespace odo::material;

NoiseTerrainMaterial::NoiseTerrainMaterial() noexcept
    : Material{"noise-terrain.vs.glsl", "noise-terrain.fs.glsl"} {}
