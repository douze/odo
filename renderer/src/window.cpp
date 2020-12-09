#include "window.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "renderer.hpp"
#include "spdlog/spdlog.h"

using namespace odo;

Window::Window(const int width, const int height) noexcept : width{width}, height{height} {
  initialize_glfw();
  create_window();
  initialize_glad();
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::initialize_glfw() const {
  if (glfwInit() == GLFW_FALSE) {
    spdlog::error("Can't initialize GLFW");
    std::exit(EXIT_FAILURE);
  }
}

void Window::create_window() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "odo", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    spdlog::error("Can't create GLFW window");
    std::exit(EXIT_FAILURE);
  }
  glfwSetCursorPosCallback(window, Renderer::cursor_position_callback);
  glfwSetMouseButtonCallback(window, Renderer::mouse_button_callback);
}

void Window::initialize_glad() const {
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    spdlog::error("Can't initialize glad");
    std::exit(EXIT_FAILURE);
  }
}

void Window::init_gui() const {
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 460 core");
}

bool Window::is_key_pressed(int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }

bool Window::is_mouse_pressed(int mouse_button) const { return glfwGetMouseButton(window, mouse_button) == GLFW_PRESS; }

void Window::mark_as_close() const { glfwSetWindowShouldClose(window, true); }

bool Window::should_close() const { return glfwWindowShouldClose(window); }

void Window::pool_events() const { glfwPollEvents(); }

void Window::swap_buffers() const { glfwSwapBuffers(window); }

void Window::set_user_pointer(Renderer* renderer) const {
  glfwSetWindowUserPointer(window, static_cast<void*>(renderer));
}
