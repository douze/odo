#ifndef MATERIAL_H
#define MATERIAL_H

#include "gui-provider.hpp"
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
class Material : public odo::GuiProvider {
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
  virtual void set_transformation_matrix(mesh::Transformation transformation) const;

  /**
   * @brief Apply the camera matrices to the material.
   * @param camera to grab matrices from
   */
  virtual void set_camera_matrices(scene::Camera camera) const;

  /**
   * @brief Set uniforms.
   */
  virtual void set_uniforms() const = 0;

  /**
   * @brief Set uniforms from parent material.
   * @param parent_material to grab uniforms from
   */
  virtual void set_uniforms_from_parent(const Material& parent_material) const {}

  /**
   * @brief Prepare the material for offscreen rendering.
   * @param width of the display
   * @param height of the display
   */
  virtual void prepare(const int width, const int height) {}

  /**
   * @brief Render the material UI to the GUI frame.
   */
  virtual void render_ui() override {}

protected:
  GLuint create_texture(const std::string& path, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter);

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
   * @param path of the texture file
   * @return the content of the texture file.
   */
  static unsigned char* read_texture_file(const std::string& path, int& width, int& height, int& image_components);

  /**
   * @brief Shaders location.
   */
  inline static const std::string SHADER_FOLDER{"resources/shaders/"};

  /**
   * @brief Textures location.
   */
  inline static const std::string TEXTURE_FOLDER{"resources/textures/"};

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
