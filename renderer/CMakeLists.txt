cmake_minimum_required(VERSION 3.15)

project(renderer
	VERSION 0.1
	DESCRIPTION "renderer library"
	LANGUAGES CXX)

add_library(renderer STATIC)
target_sources(renderer 
	PRIVATE 
      "src/renderer.cpp"
      "include/renderer.hpp")
target_include_directories(renderer
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(renderer ${CONAN_LIBS})

  
add_custom_command(TARGET renderer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/bin/resources)
