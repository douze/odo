#include "renderer.hpp"
#include "spdlog/spdlog.h"
#include "triangle.hpp"

using namespace renderer;

Renderer::Renderer(const int width, const int height) noexcept
    : width{width}, height{height} {
  initializeGlfw();
  createWindow();
  initializeGlad();
  printVersions();
}

void renderer::Renderer::initializeGlfw() const {
  if (glfwInit() == GLFW_FALSE) {
    spdlog::error("Can't initialize GLFW");
    std::exit(EXIT_FAILURE);
  }
}

void renderer::Renderer::createWindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "odo", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    spdlog::error("Can't create GLFW window");
    std::exit(EXIT_FAILURE);
  }
}

void renderer::Renderer::initializeGlad() const {
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    spdlog::error("Can't initialize glad");
    std::exit(EXIT_FAILURE);
  }
}

void renderer::Renderer::printVersions() const {
  spdlog::info("Versions:");
  spdlog::info(" > OpenGL: {0}", glGetString(GL_VERSION));
  spdlog::info(" > Renderer: {0}", glGetString(GL_RENDERER));
  spdlog::info(" > GLFW: {0}.{1}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
}

int Renderer::run() {
  mesh::Triangle triangle;
  while (!glfwWindowShouldClose(window)) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    triangle.render();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

