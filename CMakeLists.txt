cmake_minimum_required(VERSION 3.27)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/plugins)
set(CMAKE_SHARED_LIBRARY_PREFIX "raytracer_")

add_subdirectory(core)
add_subdirectory(common)
add_subdirectory(objects)
add_subdirectory(tests/unit)
