#include "renderer.hpp"
#include "glm/gtx/string_cast.hpp"
#include "mesh.hpp"
#include "spdlog/spdlog.h"
#include "triangle.hpp"

using namespace odo;

Renderer::Renderer(const int width, const int height) noexcept
    : width{width}, height{height}, last_cursor{width / 2.0f, height / 2.0f} {
  initialize_glfw();
  create_window();
  initialize_glad();
  print_versions();
  enable_debug_output();
}

void Renderer::initialize_glfw() const {
  if (glfwInit() == GLFW_FALSE) {
    spdlog::error("Can't initialize GLFW");
    std::exit(EXIT_FAILURE);
  }
}

void Renderer::create_window() {
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

  glfwSetCursorPosCallback(window, cursor_position_callback);
}

void Renderer::initialize_glad() const {
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    spdlog::error("Can't initialize glad");
    std::exit(EXIT_FAILURE);
  }
}

void Renderer::print_versions() const {
  spdlog::info("Versions:");
  spdlog::info(" > OpenGL: {0}", glGetString(GL_VERSION));
  spdlog::info(" > Renderer: {0}", glGetString(GL_RENDERER));
  spdlog::info(" > GLFW: {0}.{1}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
}

void Renderer::enable_debug_output() const {
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(
      [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
         const void* user_param) {
        std::string decoded_source;
        std::string decoded_type;
        std::string decoded_severity;

        switch (source) {
        case GL_DEBUG_SOURCE_API:
          decoded_source = "API";
          break;
        case GL_DEBUG_SOURCE_APPLICATION:
          decoded_source = "APPLICATION";
          break;
        case GL_DEBUG_SOURCE_OTHER:
          decoded_source = "OTHER";
          break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
          decoded_source = "SHADER COMPILER";
          break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
          decoded_source = "THIRD PARTY";
          break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
          decoded_source = "WINDOW SYSTEM";
          break;
        default:
          decoded_source = "UNKNOWN";
          break;
        }

        switch (type) {
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
          decoded_type = "DEPRECATED BEHAVIOR";
          break;
        case GL_DEBUG_TYPE_ERROR:
          decoded_type = "ERROR";
          break;
        case GL_DEBUG_TYPE_MARKER:
          decoded_type = "MARKER";
          break;
        case GL_DEBUG_TYPE_OTHER:
          decoded_type = "OTHER";
          break;
        case GL_DEBUG_TYPE_PERFORMANCE:
          decoded_type = "PERFORMANCE";
          break;
        case GL_DEBUG_TYPE_PORTABILITY:
          decoded_type = "PORTABILITY";
          break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
          decoded_type = "UNDEFINED BEHAVIOR";
          break;
        default:
          decoded_type = "UNKNOWN";
          break;
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
          decoded_severity = "HIGH";
          break;
        case GL_DEBUG_SEVERITY_LOW:
          decoded_severity = "LOW";
          break;
        case GL_DEBUG_SEVERITY_MEDIUM:
          decoded_severity = "MEDIUM";
          break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
          decoded_severity = "NOTIFICATION";
          break;
        default:
          decoded_severity = "UNKNOWN";
          break;
        }
        spdlog::error("{0}: {1} {2} -> {3}: {4}", id, decoded_severity.c_str(), decoded_type.c_str(),
                      decoded_source.c_str(), message);
      },
      0);
}

void Renderer::cursor_position_callback(GLFWwindow* window, double x_position, double y_position) {
  Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
  float delta_x = x_position - renderer->last_cursor.x;
  float delta_y = renderer->last_cursor.y - y_position;

  renderer->get_scene().get_main_camera().rotate(delta_x, delta_y);

  renderer->last_cursor.x = x_position;
  renderer->last_cursor.y = y_position;
}

void Renderer::process_keyboard(float delta_time) {
  scene::Camera& camera = get_scene().get_main_camera();
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.move(scene::Direction::FORWARD, delta_time);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.move(scene::Direction::BACKWARD, delta_time);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.move(scene::Direction::LEFT, delta_time);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.move(scene::Direction::RIGHT, delta_time);
  }
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
    spdlog::debug(glm::to_string(camera.position));
  }
}

void Renderer::prerun() { prepare_node(scene.get_root()); }

int Renderer::run() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  while (!glfwWindowShouldClose(window)) {
    update_timer();
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 1.0, 0.5, 1.0);
    process_keyboard(timer.delta);
    render_node(scene.get_root());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

void Renderer::update_timer() {
  float current = glfwGetTime();
  timer.delta = current - timer.last;
  timer.last = current;
}

void Renderer::render_node(scene::Node& node) const {
  if (node.is_renderable()) {
    node.get_material().use();
    node.get_material().set_transformation_matrix(node.get_transformation());
    node.get_material().set_camera_matrices(scene.get_main_camera());
    node.get_mesh().render();
  }

  for (scene::Node& child : node.get_children()) {
    render_node(child);
  }
}

void Renderer::prepare_node(scene::Node& node) const {
  if (node.is_renderable()) {
    node.get_mesh().prepare();
  }

  for (scene::Node& child : node.get_children()) {
    prepare_node(child);
  }
}
