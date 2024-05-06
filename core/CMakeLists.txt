## Source code library
add_library(raytracer_core STATIC)
target_link_libraries(raytracer_core raytracer_common)
target_include_directories(raytracer_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(raytracer_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

## Binary executable
add_executable(raytracer main.cpp)
target_link_libraries(raytracer raytracer_core)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(raytracer_core gcov)
endif()

## Add subdirectories
add_subdirectory(types)
