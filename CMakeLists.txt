cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GLFW_ImGUI_Template)

find_package(OpenGL REQUIRED)

# DEPENDENCIES
add_subdirectory(external)
include_directories(external/)


# CORE
include_directories(include)
add_subdirectory(src)

# ASSETS
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
