cmake_minimum_required(VERSION 3.15)

project(odo
	VERSION 0.1
	DESCRIPTION "OpenGL demo"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CONAN_DISABLE_CHECK_COMPILER True CACHE BOOL "" FORCE )

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

add_subdirectory(renderer)
add_subdirectory(demo)

