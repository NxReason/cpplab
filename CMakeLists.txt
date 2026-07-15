cmake_minimum_required(VERSION 3.25)
project(CppLab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(${CMAKE_SOURCE_DIR}/cmake/App.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Compiler.cmake)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/imgui)

add_subdirectory(apps)
add_subdirectory(lib)
add_subdirectory(include)