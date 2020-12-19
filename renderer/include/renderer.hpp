#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "gui.hpp"
#include "scene.hpp"
#include "window.hpp"

namespace odo {

struct Timer {
  float delta;
  float last;
};

struct Cursor {
  double x;
  double y;
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
   * @brief Callback of the mouse button.
   * @note Used to activate/deactivate cursor.
   * @param window to grab user pointer from
   * @param button pressed or release
   * @param action on the button
   * @param modifiers key flags
   */
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int modifiers);

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
  void render_node(scene::Node& node, std::optional<std::reference_wrapper<scene::Node>> parent) const;

  /**
   * @brief Prepare the node before the first render.
   * @param node to render
   * @note node may have children
   */
  void prepare_node(scene::Node& node) const;

private:
  /** Width of the display */
  int width;

  /** Heigth of the display */
  int height;

  /** Main window */
  Window window;

  /** Scene storing the meshes */
  scene::Scene scene;

  /** Timer to handle "physics" */
  Timer timer;

  /** Cursor last position */
  Cursor last_cursor;

  /** User interface */
  Gui gui;
};

} // namespace odo

#endif // RENDERER_H
