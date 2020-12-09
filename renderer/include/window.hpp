#ifndef WINDOW_HPP
#define WINDOW_HPP

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace odo {

class Renderer;

/**
 * @brief Main window of the application.
 * @note Contains the graphic context.
 */
class Window {
public:
  /**
   * @brief Create a graphic window for the rendering context.
   * @note The window will listen to user inputs.
   * @param width of the window
   * @param height of the window
   */
  explicit Window(const int width, const int height) noexcept;

  /**
   * @brief Destroy the window & the graphic context.
   */
  ~Window();

  /**
   * @brief Initialize the user interface.
   */
  void init_gui() const;

  /**
   * @param key to check
   * @return true if key is pressed.
   */
  bool is_key_pressed(int key) const;

  /**
   * @param mouse to check
   * @return true if mouse_button is pressed.
   */
  bool is_mouse_pressed(int mouse_button) const;

  /**
   * @brief Set the close flag to the window.
   */
  void mark_as_close() const;

  /**
   * @return true if the window should close..
   */
  bool should_close() const;

  /**
   * @brief Process pending events.
   */
  void pool_events() const;

  /**
   * @brief Swap back & front buffers.
   */
  void swap_buffers() const;

  /**
   * @brief Set the renderer as the user pointer.
   * @param renderer to assign
   */
  void set_user_pointer(Renderer* renderer) const;

private:
  /**
   * @brief Initialize GLFW.
   * @note May exit the application when failing.
   */
  void initialize_glfw() const;

  /**
   * @brief Create the window, using custom flags.
   * @note May exit the application when failing.
   */
  void create_window();

  /**
   * @brief Initialize glad with current OpenGL context.
   * @note May exit the application when failing.
   */
  void initialize_glad() const;

private:
  /** Handler for current window */
  GLFWwindow* window;

  /** Width of the display */
  int width;

  /** Heigth of the display */
  int height;
};

} // namespace odo

#endif // WINDOW_HPP
