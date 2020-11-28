#ifndef VERTEXCOLORMATERIAL_H
#define VERTEXCOLORMATERIAL_H

#include "material.hpp"

namespace odo::material {

/**
 * @brief Define one color per vertex.
 */
class VertexColorMaterial : public Material {
public:
  explicit VertexColorMaterial() noexcept;
};

} // namespace odo::material

#endif // VERTEXCOLORMATERIAL_H
