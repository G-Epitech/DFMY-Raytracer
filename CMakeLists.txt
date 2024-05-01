cmake_minimum_required(VERSION 3.27)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(src)
add_subdirectory(tests/unit)
