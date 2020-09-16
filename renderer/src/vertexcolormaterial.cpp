#include "vertexcolormaterial.hpp"

using namespace renderer::material;

VertexColorMaterial::VertexColorMaterial() noexcept
    : Material{"vertexcolor.vs.glsl", "vertexcolor.fs.glsl"} {}
