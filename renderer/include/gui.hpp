#ifndef GUI_HPP
#define GUI_HPP

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.hpp"
#include <imgui.h>

namespace odo {

/**
 * @brief User interface.
 */
class Gui {
public:
  /**
   * @brief Create a user interface for the window.
   * @param window to create UI for
   */
  explicit Gui(const Window& window) noexcept;

  /**
   * @brief Render the user interface.
   */
  void render_ui();

  /**
   * @return true if UI should dispath mouse to main application.
   */
  bool should_dispatch_mouse() const;

private:
  bool show_demo_window;
  bool show_another_window;
  ImVec4 clear_color;
};

} // namespace odo

#endif // GUI_HPP
