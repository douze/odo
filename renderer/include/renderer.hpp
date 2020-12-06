#ifndef RENDERER_H
#define RENDERER_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "scene.hpp"

namespace odo {

struct Timer {
  float delta;
  float last;
};

struct Cursor {
  float x;
  float y;
};

/**
 * @brief Render the scene to the display.
 */
class Renderer {
public:
  /**
   * @brief Create a renderer, initializing the display.
   * @param width of the display
   * @param height of the display
   */
  explicit Renderer(const int width, const int height) noexcept;

  /**
   * @brief Callback of the cursor position.
   * @note Mainly used to rotate main camera.
   * @param window to grab user pointer from
   * @param x_position of the cursor
   * @param y_position of the cursor
   */
  static void cursor_position_callback(GLFWwindow* window, double x_position, double y_position);

  /**
   * @brief Method used before the run loop.
   */
  void prerun();

  /**
   * @brief Run the main loop.
   */
  int run();

  /**
   * @return the scene graph.
   */
  scene::Scene& get_scene() { return scene; }

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

  /**
   * @brief Print various information about versions.
   */
  void print_versions() const;

  /**
   * @brief Enable OpenGL debug output.
   */
  void enable_debug_output() const;

  /**
   * @brief Update delta time.
   * @note Naive approch.
   */
  void update_timer();

  /**
   * @brief Process the user keyboard.
   * @param delta_time from previous update
   */
  void process_keyboard(float delta_time);

  /**
   * @brief Render a scene node.
   * @param node to render
   * @note node may have children
   */
  void render_node(scene::Node& node) const;

  /**
   * @brief Prepare the node before the first render.
   * @param node to render
   * @note node may have children
   */
  void prepare_node(scene::Node& node) const;

private:
  /** Handler for current window */
  GLFWwindow* window;

  /** Width of the display */
  int width;

  /** Heigth of the display */
  int height;

  /** Scene storing the meshes */
  scene::Scene scene;

  /** Timer to handle "physics" */
  Timer timer;

  /** Cursor last position */
  Cursor last_cursor;
};

} // namespace odo

#endif // RENDERER_H
