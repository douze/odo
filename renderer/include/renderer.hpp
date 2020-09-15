#ifndef RENDERER_H
#define RENDERER_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace renderer {

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
   * @brief Run the main loop.
   */
  int run();

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

private:
  /** Handler for current window */
  GLFWwindow* window;

  /** Width of the display */
  int width;

  /** Heigth of the display */
  int height;
};
} // namespace renderer

#endif // RENDERER_H
