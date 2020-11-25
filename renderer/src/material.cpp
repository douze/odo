#include "material.hpp"
#include "camera.hpp"
#include "spdlog/spdlog.h"
#include "transformation.hpp"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

using namespace odo::material;

#include <iostream>

Material::Material(const std::string& vsPath,
                   const std::string& fsPath) noexcept {
  vs = createShaderProgram(GL_VERTEX_SHADER, vsPath);
  fs = createShaderProgram(GL_FRAGMENT_SHADER, fsPath);

  glCreateProgramPipelines(1, &pipeline);
  glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vs);
  glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fs);
}

Material::Material(const std::string& vsPath, const std::string& tcsPath,
                   const std::string& tesPath, const std::string& gsPath,
                   const std::string& fsPath) noexcept {
  vs = createShaderProgram(GL_VERTEX_SHADER, vsPath);
  tcs = createShaderProgram(GL_TESS_CONTROL_SHADER, tcsPath);
  tes = createShaderProgram(GL_TESS_EVALUATION_SHADER, tesPath);
  gs = createShaderProgram(GL_GEOMETRY_SHADER, gsPath);
  fs = createShaderProgram(GL_FRAGMENT_SHADER, fsPath);

  glCreateProgramPipelines(1, &pipeline);
  glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vs);
  glUseProgramStages(pipeline, GL_TESS_CONTROL_SHADER_BIT, tcs);
  glUseProgramStages(pipeline, GL_TESS_EVALUATION_SHADER_BIT, tes);
  glUseProgramStages(pipeline, GL_GEOMETRY_SHADER_BIT, gs);
  glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fs);
}

GLuint Material::createShaderProgram(GLenum type,
                                     const std::string& path) const {
  std::string source = readShaderFile(path);
  addImports(source);
  const char* csource = source.c_str();
  const GLuint shaderProgram = glCreateShaderProgramv(type, 1, &csource);
  checkLinkStatus(shaderProgram, path);
  return shaderProgram;
}

std::string Material::readShaderFile(const std::string& path) {
  std::ifstream file{SHADER_FOLDER + path};
  return std::string{(std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>()};
}

void Material::addImports(std::string& content) const {
  const std::string import = "#import ";
  const std::string eol = "\n";
  std::string::size_type start = 0;
  std::string::size_type end = 0;
  std::string filename;
  std::string subcontent;

  while ((start = content.find(import, start)) != std::string::npos) {
    end = content.find(eol, start);
    filename =
        content.substr(start + import.length(), end - start - import.length());
    subcontent = readShaderFile(filename);
    content.replace(start, end - start, subcontent + eol);
    start = end + 1;
  }
}

void Material::checkLinkStatus(GLuint program, const std::string& path) const {
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
    spdlog::error("Invalid shader {0}: {1}", path,
                  std::string{infoLog.begin(), infoLog.end()});
  }
}

void Material::use() const { glBindProgramPipeline(pipeline); }

void Material::setTransformationMatrix(
    mesh::Transformation transformation) const {
  glProgramUniformMatrix4fv(vs, 0, 1, GL_FALSE,
                            glm::value_ptr(transformation.getMatrix()));
}

void Material::setCameraMatrices(scene::Camera camera) const {
  glProgramUniformMatrix4fv(vs, 1, 1, GL_FALSE,
                            glm::value_ptr(camera.getViewMatrix()));
  glProgramUniformMatrix4fv(vs, 2, 1, GL_FALSE,
                            glm::value_ptr(camera.getProjectionMatrix()));
}
