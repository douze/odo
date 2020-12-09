#include "renderer.hpp"
#include "glm/gtx/string_cast.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "mesh.hpp"
#include "spdlog/spdlog.h"
#include "triangle.hpp"

using namespace odo;

Renderer::Renderer(const int width, const int height) noexcept
    : width{width}, height{height}, last_cursor{width / 2.0f, height / 2.0f} {
  initialize_glfw();
  create_window();
  initialize_glad();
  print_versions();
  enable_debug_output();
}

void Renderer::initialize_glfw() const {
  if (glfwInit() == GLFW_FALSE) {
    spdlog::error("Can't initialize GLFW");
    std::exit(EXIT_FAILURE);
  }
}

void Renderer::create_window() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "odo", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    spdlog::error("Can't create GLFW window");
    std::exit(EXIT_FAILURE);
  }
  glfwSetWindowUserPointer(window, static_cast<void*>(this));
  //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Renderer::initialize_glad() const {
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    spdlog::error("Can't initialize glad");
    std::exit(EXIT_FAILURE);
  }
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
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
    return;

  ImGuiIO& io = ImGui::GetIO();
  spdlog::debug(io.WantCaptureMouse);
  if (io.WantCaptureMouse == true)
    return;

  Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
  float delta_x = x_position - renderer->last_cursor.x;
  float delta_y = renderer->last_cursor.y - y_position;

  renderer->get_scene().get_main_camera().rotate(delta_x, delta_y);

  renderer->last_cursor.x = x_position;
  renderer->last_cursor.y = y_position;
}

void Renderer::mouse_button_callback(GLFWwindow* window, int button, int action, int modifiers) {

  Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);
      renderer->last_cursor.x = xpos;
      renderer->last_cursor.y = ypos;
    } else if (action == GLFW_RELEASE) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
  }
}

void Renderer::process_keyboard(float delta_time) {
  // Exit
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  // Move camera
  ImGuiIO& io = ImGui::GetIO();
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
    return;
  scene::Camera& camera = get_scene().get_main_camera();
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.move(scene::Direction::FORWARD, delta_time);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.move(scene::Direction::BACKWARD, delta_time);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.move(scene::Direction::LEFT, delta_time);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.move(scene::Direction::RIGHT, delta_time);
  }
}

void Renderer::prerun() { prepare_node(scene.get_root()); }

int Renderer::run() {
  /* IMGUI */
  // Setup Dear ImGui context IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  const char* glsl_version = "#version 130";
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use
  // ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g.
  // use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling
  // ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double
  // backslash \\ !
  // io.Fonts->AddFontDefault();
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL,
  // io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != NULL);

  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  /* IMGUI */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  while (!glfwWindowShouldClose(window)) {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your
    // inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two
    // flags.
    glfwPollEvents();

    /* IMGUI */
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to
    // learn more about Dear ImGui!).
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
      ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                  ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
      ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have
                                                            // a closing button that will clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }

    // Rendering
    ImGui::Render();
    /* IMGUI */

    update_timer();
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 1.0, 0.5, 1.0);
    process_keyboard(timer.delta);
    render_node(scene.get_root());

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}

void Renderer::update_timer() {
  float current = glfwGetTime();
  timer.delta = current - timer.last;
  timer.last = current;
}

void Renderer::render_node(scene::Node& node) const {
  if (node.is_renderable()) {
    node.get_material().use();
    node.get_material().set_transformation_matrix(node.get_transformation());
    node.get_material().set_camera_matrices(scene.get_main_camera());
    node.get_mesh().render();
  }

  for (scene::Node& child : node.get_children()) {
    render_node(child);
  }
}

void Renderer::prepare_node(scene::Node& node) const {
  if (node.is_renderable()) {
    node.get_mesh().prepare();
  }

  for (scene::Node& child : node.get_children()) {
    prepare_node(child);
  }
}
