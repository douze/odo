cmake_minimum_required(VERSION 3.15)

project(renderer
	VERSION 0.1
	DESCRIPTION "renderer library"
	LANGUAGES CXX)

add_library(renderer STATIC)
target_sources(renderer 
	PRIVATE 
      "src/renderer.cpp"
      "src/material.cpp"
      "src/vertex-color-material.cpp"
      "src/scene.cpp"
      "src/mesh.cpp"
      "src/transformation.cpp"
      "src/camera.cpp"
      "src/terrain.cpp"
      "src/terrain-material.cpp"
      "src/full-screen-quad.cpp"
      "src/noise-terrain-material.cpp"
      "src/gui.cpp"
      "src/window.cpp"
      "src/imgui_impl_glfw.cpp"
      "src/imgui_impl_opengl3.cpp"
      "include/renderer.hpp"
      "include/material.hpp"
      "include/vertex-color-material.hpp"
      "include/scene.hpp"
      "include/mesh.hpp"
      "include/transformation.hpp"
      "include/camera.hpp"
      "include/terrain.hpp"
      "include/terrain-material.hpp"
      "include/full-screen-quad.hpp"
      "include/noise-terrain-material.hpp"
      "include/gui.hpp"
      "include/window.hpp"
      "include/imgui_impl_glfw.h"
      "include/imgui_impl_opengl3.h")
target_include_directories(renderer
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(renderer ${CONAN_LIBS})

  
add_custom_command(TARGET renderer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/bin/resources)
