#include "gui.hpp"
#include <imgui.h>

using namespace odo;

Gui::Gui(const Window& window) noexcept {
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  window.init_gui();
}

void Gui::render_ui(scene::Scene& scene) {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // I need examples for now
  ImGui::ShowDemoWindow();

  // Real UI
  ImGui::Begin("OpenGL Demo");
  scene.get_main_camera().render_ui();
  scene.render_ui(scene.root);
  ImGui::End();

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Gui::should_dispatch_mouse() const { return ImGui::GetIO().WantCaptureMouse == false; }
