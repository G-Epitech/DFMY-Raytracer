cmake_minimum_required(VERSION 3.22)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(core)
add_subdirectory(common)
add_subdirectory(tests/unit)

target_link_libraries(raytracer config++)
