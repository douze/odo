#ifndef RENDERER_H
#define RENDERER_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "scene.hpp"

namespace renderer {

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
   * @brief Method used before the run loop.
   */
  void prerun();

  /**
   * @brief Run the main loop.
   */
  int run();

  /**
   * @brief Return the scene.
   */
  scene::Scene& getScene() { return scene; }

private:
  /**
   * @brief Initialize GLFW.
   * @note May exit the application when failing.
   */
  void initializeGlfw() const;

  /**
   * @brief Create the window, using custom flags.
   * @note May exit the application when failing.
   */
  void createWindow();

  /**
   * @brief Initialize glad with current OpenGL context.
   * @note May exit the application when failing.
   */
  void initializeGlad() const;

  /**
   * @brief Print various information about versions.
   */
  void printVersions() const;

  /**
   * @brief Enable OpenGL debug output.
   */
  void enableDebugOutput() const;

  /**
   * @brief Update delta time.
   * @note Naive approch.
   */
  void updateTimer();

  /**
   * @brief Process the user keyboard.
   * @param deltaTime from previous update
   */
  void processKeyboard(float deltaTime);

  /**
   * @brief Process the user mouse.
   * @param deltaTime from previous update
   */
  void processMouse(float deltaTime);

  /**
   * @brief Render a scene node.
   * @param node to render
   * @note node may have children
   */
  void renderNode(scene::Node& node) const;

  /**
   * @brief Prepare the node before the first render.
   * @param node to render
   * @note node may have children
   */
  void prepareNode(scene::Node& node) const;

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
  Cursor cursor;
};

} // namespace renderer

#endif // RENDERER_H
