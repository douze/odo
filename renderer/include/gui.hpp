#ifndef GUI_HPP
#define GUI_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GLFWwindow;

namespace odo {

class Gui {
public:
  Gui();

  void setup(GLFWwindow* window) const;

  void render_frame();

  bool show_demo_window;
  bool show_another_window;

  ImVec4 clear_color;
};

} // namespace odo

#endif // GUI_HPP
