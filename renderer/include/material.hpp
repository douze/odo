#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <string>

namespace odo {

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
  explicit Material(const std::string& vs_path, const std::string& fs_path) noexcept;

  /**
   * @brief Create a material from vertex, tessellation, geometry & fragment
   * shaders.
   */
  explicit Material(const std::string& vs_path, const std::string& tcs_path, const std::string& tes_path,
                    const std::string& gs_path, const std::string& fs_path) noexcept;
  /**
   * @brief Use this material for the next rendering.
   */
  void use() const;

  /**
   * @brief Apply the transformation to the material.
   * @param transformation to apply
   */
  void set_transformation_matrix(mesh::Transformation transformation) const;

  /**
   * @brief Apply the camera matrices to the material.
   * @param camera to grab matrices from
   */
  void set_camera_matrices(scene::Camera camera) const;

  /**
   * @brief Render the material UI to the GUI frame.
   */
  virtual void render_ui() = 0;

  /**
   * @brief Set uniforms.
   */
  virtual void set_uniforms() const = 0;

  virtual void prepare_offscreen() {}

  virtual GLuint get_offscreen_texture() const { return 0; }

  virtual GLuint get_offscreen_fbo() const { return 0; }

private:
  /**
   * @param path of the shader file
   * @return the content of the shader file.
   */
  static std::string read_shader_file(const std::string& path);

  /**
   * @brief Parse shader content and replace #import directives with corresponding string.
   * @param content of the shader to enrich
   */
  void add_imports(std::string& content) const;

  /**
   * @param type of shader
   * @param path of the shader file
   * @return the created shader program.
   * */
  GLuint create_shader_program(GLenum type, const std::string& path) const;

  /**
   * @brief Check the program link status.
   * @note Only print errors - no exception or exit code.
   * @param program to check
   * @param path of the shader program
   */
  void check_link_status(GLuint program, const std::string& path) const;

  /**
   * @brief Shaders location.
   */
  inline static const std::string SHADER_FOLDER{"resources/shaders/"};

private:
  /** Program pipeline */
  GLuint pipeline;

protected:
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
} // namespace odo

#endif // MATERIAL_H
