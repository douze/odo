#ifndef VERTEXCOLORMATERIAL_H
#define VERTEXCOLORMATERIAL_H

#include "material.hpp"

namespace renderer {
namespace material {

/**
 * @brief Define one color per vertex.
 */
class VertexColorMaterial : public Material {
public:
  explicit VertexColorMaterial() noexcept;
};

} // namespace material
} // namespace renderer
#endif // VERTEXCOLORMATERIAL_H
