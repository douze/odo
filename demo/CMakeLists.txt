cmake_minimum_required( VERSION 3.15 )

project(demo
	VERSION 0.1
	DESCRIPTION "demo binary"
	LANGUAGES CXX)

add_executable(demo)
target_sources(demo PRIVATE src/main.cpp)
target_link_libraries(demo PRIVATE renderer)
