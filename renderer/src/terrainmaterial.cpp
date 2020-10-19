#include "terrainmaterial.hpp"

using namespace renderer::material;

TerrainMaterial::TerrainMaterial() noexcept
    : Material{"terrain.vs.glsl", "terrain.tcs.glsl", "terrain.tes.glsl",
               "terrain.fs.glsl"} {}
