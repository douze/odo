#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <string>

namespace renderer {

namespace mesh {
class Transformation;
}

namespace scene {
class Camera;
}

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

  explicit Material(const std::string& vsPath, const std::string& tcsPath,
                    const std::string& tesPath, const std::string& gsPath,
                    const std::string& fsPath) noexcept;
  /**
   * @brief Use this material for the next rendering.
   */
  void use() const;

  /**
   * @brief Apply the transformation to the material
   * @param transformation to apply
   */
  void setTransformationMatrix(mesh::Transformation transformation) const;

  void setCameraMatrices(scene::Camera camera) const;

private:
  /**
   * @brief Read a shader file from the resources folder.
   * @param path of the shader file
   */
  static std::string readShaderFile(const std::string& path);

  /**
   * @brief Create a shader program.
   * @param type of shader
   * @param path of the shader file
   * */
  GLuint createShaderProgram(GLenum type, const std::string& path);

  /**
   * @brief Shaders location.
   */
  inline static const std::string SHADER_FOLDER{"resources/shaders/"};

private:
  /** Program pipeline */
  GLuint pipeline;

  /** Vertex shader program */
  GLuint vs;

  /** Tessellation control program */
  GLuint tcs;
  
  /** Tessellation evaluation program */
  GLuint tes;
  
  /** Geometry shader */
  GLuint gs;

  /** Fragment shader program */
  GLuint fs;
};

} // namespace material
} // namespace renderer

#endif // MATERIAL_H
