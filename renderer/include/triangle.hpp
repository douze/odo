#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>

namespace renderer {
namespace mesh {

struct vertex_t {
  float x, y, z;
  float r, g, b;
};

static const char* vertexShaderText =
    "#version 460\n"
    "out gl_PerVertex { vec4 gl_Position; };\n"
    "layout (location = 0) in vec3 vPos;\n"
    "layout (location = 1) in vec3 vCol;\n"
    "out V_OUT { vec3 color; } v_out;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(vPos, 1.0);\n"
    "    v_out.color = vCol;\n"
    "}\n";

static const char* fragmentShaderText =
    "#version 460\n"
    "in V_OUT { vec3 color; } v_out;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "    color = vec4(v_out.color, 1.0);\n"
    "}\n";

/**
 * @brief Triangle mesh.
 * @note Test class, will dissapear in a near future.
 */
class Triangle {
public:
  explicit Triangle() noexcept;

  void render() const;

private:
  GLuint vao;
  GLuint program;
};

} // namespace mesh
} // namespace renderer

#endif // TRIANGLE_H
