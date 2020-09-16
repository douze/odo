#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <string>

namespace renderer {
namespace material {

/**
 * @brief Define the visual aspect of the mesh.
 * @note Must be derivated.
 */
class Material {
public:
  /**
   * @brief Create a material from vertex & fragment shaders.
   */
  explicit Material(const std::string& vsPath,
                    const std::string& fsPath) noexcept;

  /**
   * @brief Use this material for the next rendering.
   */
  void use() const;

private:
  /**
   * @brief Read a shader file from the resources folder.
   * @param path of the shader file
   */
  static std::string readShaderFile(const std::string& path);

  /**
   * @brief Create a shader.
   * @param type of shader
   * @param path of the shader file
   * */
  GLuint createShader(GLenum type, const std::string& path);

  /**
   * @brief Shaders location.
   */
  inline static const std::string SHADER_FOLDER{"resources/shaders/"};

private:
  /** Program pipeline */
  GLuint pipeline;
};

} // namespace material
} // namespace renderer

#endif // MATERIAL_H
