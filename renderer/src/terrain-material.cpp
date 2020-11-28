#include "terrain-material.hpp"

using namespace odo::material;

TerrainMaterial::TerrainMaterial() noexcept
    : Material{"terrain.vs.glsl", "terrain.tcs.glsl", "terrain.tes.glsl",
               "terrain.gs.glsl", "terrain.fs.glsl"} {}
