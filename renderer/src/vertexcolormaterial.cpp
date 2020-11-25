#include "vertexcolormaterial.hpp"

using namespace odo::material;

VertexColorMaterial::VertexColorMaterial() noexcept
    : Material{"vertexcolor.vs.glsl", "vertexcolor.fs.glsl"} {}
