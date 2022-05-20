#include "renderer.hpp"
#include "glm/gtx/string_cast.hpp"
#include "mesh.hpp"
#include "spdlog/spdlog.h"
#include <GLFW/glfw3.h>

using namespace odo;

Renderer::Renderer(const int width, const int height) noexcept
    : width{width}, height{height}, window{width, height}, last_cursor{width / 2.0f, height / 2.0f}, gui{window} {
  print_versions();
  enable_debug_output();
  window.set_user_pointer(this);
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

  if (!renderer->window.is_mouse_pressed(GLFW_MOUSE_BUTTON_LEFT) || !renderer->gui.should_dispatch_mouse())
    return;

  Cursor delta{x_position - renderer->last_cursor.x, renderer->last_cursor.y - y_position};
  renderer->get_scene().get_main_camera().rotate(delta.x, delta.y);
  renderer->last_cursor = {x_position, y_position};
}

void Renderer::mouse_button_callback(GLFWwindow* window, int button, int action, int modifiers) {
  Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

  if (!renderer->gui.should_dispatch_mouse())
    return;

  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);
      renderer->last_cursor = {xpos, ypos};
    } else if (action == GLFW_RELEASE) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
  }
}

void Renderer::process_keyboard(float delta_time) {
  if (window.is_key_pressed(GLFW_KEY_ESCAPE)) {
    window.mark_as_close();
  }

  if (!window.is_mouse_pressed(GLFW_MOUSE_BUTTON_LEFT) || !gui.should_dispatch_mouse())
    return;

  scene::Camera& camera = get_scene().get_main_camera();
  if (window.is_key_pressed(GLFW_KEY_W)) {
    camera.move(scene::Direction::FORWARD, delta_time);
  }
  if (window.is_key_pressed(GLFW_KEY_S)) {
    camera.move(scene::Direction::BACKWARD, delta_time);
  }
  if (window.is_key_pressed(GLFW_KEY_A)) {
    camera.move(scene::Direction::LEFT, delta_time);
  }
  if (window.is_key_pressed(GLFW_KEY_D)) {
    camera.move(scene::Direction::RIGHT, delta_time);
  }
}

void Renderer::prepare() { prepare_node(scene.get_root()); }

void Renderer::prepare_node(scene::Node& node) const {
  if (node.is_renderable()) {
    node.prepare(width, height);
  }

  for (scene::Node& child : node.get_children()) {
    prepare_node(child);
  }
}

int Renderer::run() {
  set_render_state();
  while (!window.should_close()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    window.pool_events();
    update_timer();
    process_keyboard(timer.delta);
    render_node(scene.get_root(), std::nullopt);
    gui.render_ui(scene);
    window.swap_buffers();
  }
  return 0;
}

void Renderer::update_timer() {
  float current = glfwGetTime();
  timer.delta = current - timer.last;
  timer.last = current;
}

void Renderer::render_node(scene::Node& node, std::optional<std::reference_wrapper<scene::Node>> parent) const {
  if (node.is_renderable()) {
    const bool rendered = node.render(scene.get_main_camera(), parent);
    if (rendered && node.should_restore_render_state()) {
      set_render_state();
    }
  }

  for (scene::Node& child : node.get_children()) {
    render_node(child, std::make_optional<std::reference_wrapper<scene::Node>>(node));
  }
}

void Renderer::set_render_state() const {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glViewport(0, 0, width, height);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
