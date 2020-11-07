#include "renderer.hpp"
#include "mesh.hpp"
#include "spdlog/spdlog.h"
#include "triangle.hpp"

using namespace renderer;

Renderer::Renderer(const int width, const int height) noexcept
    : width{width}, height{height} {
  initializeGlfw();
  createWindow();
  initializeGlad();
  printVersions();
  enableDebugOutput();
}

void Renderer::initializeGlfw() const {
  if (glfwInit() == GLFW_FALSE) {
    spdlog::error("Can't initialize GLFW");
    std::exit(EXIT_FAILURE);
  }
}

void Renderer::createWindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "odo", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    spdlog::error("Can't create GLFW window");
    std::exit(EXIT_FAILURE);
  }
  glfwSetWindowUserPointer(window, static_cast<void*>(this));
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Renderer::initializeGlad() const {
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    spdlog::error("Can't initialize glad");
    std::exit(EXIT_FAILURE);
  }
}

void Renderer::printVersions() const {
  spdlog::info("Versions:");
  spdlog::info(" > OpenGL: {0}", glGetString(GL_VERSION));
  spdlog::info(" > Renderer: {0}", glGetString(GL_RENDERER));
  spdlog::info(" > GLFW: {0}.{1}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
}

void Renderer::enableDebugOutput() const {
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(
      [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
         const GLchar* message, const void* userParam) {
        std::string decodedSource;
        std::string decodedType;
        std::string decodedSeverity;

        switch (source) {
        case GL_DEBUG_SOURCE_API:
          decodedSource = "API";
          break;
        case GL_DEBUG_SOURCE_APPLICATION:
          decodedSource = "APPLICATION";
          break;
        case GL_DEBUG_SOURCE_OTHER:
          decodedSource = "OTHER";
          break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
          decodedSource = "SHADER COMPILER";
          break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
          decodedSource = "THIRD PARTY";
          break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
          decodedSource = "WINDOW SYSTEM";
          break;
        default:
          decodedSource = "UNKNOWN";
          break;
        }

        switch (type) {
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
          decodedType = "DEPRECATED BEHAVIOR";
          break;
        case GL_DEBUG_TYPE_ERROR:
          decodedType = "ERROR";
          break;
        case GL_DEBUG_TYPE_MARKER:
          decodedType = "MARKER";
          break;
        case GL_DEBUG_TYPE_OTHER:
          decodedType = "OTHER";
          break;
        case GL_DEBUG_TYPE_PERFORMANCE:
          decodedType = "PERFORMANCE";
          break;
        case GL_DEBUG_TYPE_PORTABILITY:
          decodedType = "PORTABILITY";
          break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
          decodedType = "UNDEFINED BEHAVIOR";
          break;
        default:
          decodedType = "UNKNOWN";
          break;
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
          decodedSeverity = "HIGH";
          break;
        case GL_DEBUG_SEVERITY_LOW:
          decodedSeverity = "LOW";
          break;
        case GL_DEBUG_SEVERITY_MEDIUM:
          decodedSeverity = "MEDIUM";
          break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
          decodedSeverity = "NOTIFICATION";
          break;
        default:
          decodedSeverity = "UNKNOWN";
          break;
        }
        spdlog::error("{0}: {1} {2} -> {3}: {4}", id, decodedSeverity.c_str(),
                      decodedType.c_str(), decodedSource.c_str(), message);
      },
      0);
}

void Renderer::processKeyboard(float deltaTime) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    getScene().getCamera().move(scene::Direction::FORWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    getScene().getCamera().move(scene::Direction::BACKWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    getScene().getCamera().move(scene::Direction::LEFT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    getScene().getCamera().move(scene::Direction::RIGHT, deltaTime);
  }
}

void Renderer::processMouse(float deltaTime) {
  // TODO
  getScene().getCamera().rotate(0, 0, deltaTime);
}

#include <iostream>

void Renderer::prerun() { prepareNode(scene.getRoot()); }

int Renderer::run() {
  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(window)) {
    updateTimer();
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 1.0, 0.5, 1.0);
    processKeyboard(timer.delta);
    processMouse(timer.delta);
    renderNode(scene.getRoot());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

void Renderer::updateTimer() {
  float current = glfwGetTime();
  timer.delta = current - timer.last;
  timer.last = current;
}

void Renderer::renderNode(scene::Node& node) const {
  if (node.isRenderable()) {
    node.getMaterial().use();
    node.getMaterial().setTransformationMatrix(node.getTransformation());
    node.getMaterial().setCameraMatrices(scene.getCamera());
    node.getMesh().render();
  }

  for (scene::Node& child : node.getChildren()) {
    renderNode(child);
  }
}

void Renderer::prepareNode(scene::Node& node) const {
  if (node.isRenderable()) {
    node.getMesh().prepare();
  }

  for (scene::Node& child : node.getChildren()) {
    prepareNode(child);
  }
}
