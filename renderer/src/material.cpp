#include "material.hpp"
#include "camera.hpp"
#include "spdlog/spdlog.h"
#include "transformation.hpp"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

using namespace odo::material;

#include <iostream>

Material::Material(const std::string& vs_path, const std::string& fs_path) noexcept {
  vs = create_shader_program(GL_VERTEX_SHADER, vs_path);
  fs = create_shader_program(GL_FRAGMENT_SHADER, fs_path);

  glCreateProgramPipelines(1, &pipeline);
  glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vs);
  glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fs);
}

Material::Material(const std::string& vs_path, const std::string& tcs_path, const std::string& tes_path,
                   const std::string& gs_path, const std::string& fs_path) noexcept {
  vs = create_shader_program(GL_VERTEX_SHADER, vs_path);
  tcs = create_shader_program(GL_TESS_CONTROL_SHADER, tcs_path);
  tes = create_shader_program(GL_TESS_EVALUATION_SHADER, tes_path);
  gs = create_shader_program(GL_GEOMETRY_SHADER, gs_path);
  fs = create_shader_program(GL_FRAGMENT_SHADER, fs_path);

  glCreateProgramPipelines(1, &pipeline);
  glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vs);
  glUseProgramStages(pipeline, GL_TESS_CONTROL_SHADER_BIT, tcs);
  glUseProgramStages(pipeline, GL_TESS_EVALUATION_SHADER_BIT, tes);
  glUseProgramStages(pipeline, GL_GEOMETRY_SHADER_BIT, gs);
  glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fs);
}

GLuint Material::create_shader_program(GLenum type, const std::string& path) const {
  std::string source = read_shader_file(path);
  add_imports(source);
  const char* csource = source.c_str();
  const GLuint shader_program = glCreateShaderProgramv(type, 1, &csource);
  check_link_status(shader_program, path);
  return shader_program;
}

std::string Material::read_shader_file(const std::string& path) {
  std::ifstream file{SHADER_FOLDER + path};
  return std::string{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
}

void Material::add_imports(std::string& content) const {
  const std::string import = "#import ";
  const std::string eol = "\n";
  std::string::size_type start = 0;
  std::string::size_type end = 0;
  std::string filename;
  std::string subcontent;

  // Find import directive and replace them with corresponding file content
  while ((start = content.find(import, start)) != std::string::npos) {
    end = content.find(eol, start);
    filename = content.substr(start + import.length(), end - start - import.length());
    subcontent = read_shader_file(filename);
    content.replace(start, end - start, subcontent + eol);
    start = end + 1;
  }
}

void Material::check_link_status(GLuint program, const std::string& path) const {
  GLint is_linked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);
    spdlog::error("Invalid shader {0}: {1}", path, std::string{info_log.begin(), info_log.end()});
  }
}

void Material::use() const { glBindProgramPipeline(pipeline); }

void Material::set_transformation_matrix(mesh::Transformation transformation) const {
  glProgramUniformMatrix4fv(vs, 0, 1, GL_FALSE, glm::value_ptr(transformation.get_matrix()));
}

void Material::set_camera_matrices(scene::Camera camera) const {
  glProgramUniformMatrix4fv(vs, 1, 1, GL_FALSE, glm::value_ptr(camera.get_view_matrix()));
  glProgramUniformMatrix4fv(vs, 2, 1, GL_FALSE, glm::value_ptr(camera.get_projection_matrix()));
}
