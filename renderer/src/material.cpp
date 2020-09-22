#include "material.hpp"
#include "spdlog/spdlog.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

using namespace renderer::material;

Material::Material(const std::string& vsPath,
                   const std::string& fsPath) noexcept {
  vs = createShaderProgram(GL_VERTEX_SHADER, vsPath);
  fs = createShaderProgram(GL_FRAGMENT_SHADER, fsPath);

  glCreateProgramPipelines(1, &pipeline);
  glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vs);
  glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fs);
}

GLuint Material::createShaderProgram(GLenum type, const std::string& path) {
  const std::string source = readShaderFile(path);
  const char* csource = source.c_str();
  return glCreateShaderProgramv(type, 1, &csource);
}

std::string Material::readShaderFile(const std::string& path) {
  spdlog::debug("Reading shader {0}", path);
  std::ifstream file{SHADER_FOLDER + path};
  return std::string{(std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>()};
}

void Material::use() const { glBindProgramPipeline(pipeline); }

void Material::setTransformation(mesh::Transformation transformation) const {
  glProgramUniformMatrix4fv(vs, 0, 1, GL_FALSE,
                            glm::value_ptr(transformation.getMatrix()));
}
