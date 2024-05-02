## Source code library
add_library(raytracer-core STATIC)
target_link_libraries(raytracer-core raytracer-common)
target_include_directories(raytracer-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(raytracer-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../core)

## Binary executable
add_executable(raytracer main.cpp)
target_link_libraries(raytracer raytracer-core)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(raytracer-core gcov)
endif()

## Add subdirectories
add_subdirectory(types)
