#include "noiseterrainmaterial.hpp"

using namespace renderer::material;

NoiseTerrainMaterial::NoiseTerrainMaterial() noexcept
    : Material{"noise-terrain.vs.glsl", "noise-terrain.fs.glsl"} {}
