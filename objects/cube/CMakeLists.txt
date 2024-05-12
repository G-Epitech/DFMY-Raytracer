# Setup Raytracer Cube library
add_library(raytracer_cube SHARED)

# Link Raytracer Cube library
target_link_libraries(raytracer_cube PRIVATE raytracer_common)

# Add sources to Raytracer Cube library
target_sources(raytracer_cube PRIVATE
    export.cpp
    src/CubeProvider.hpp
    src/CubeProvider.cpp
    src/Cube.hpp
    src/Cube.cpp
)

# Include directories for Raytracer Cube library
target_include_directories(raytracer_cube PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(raytracer_cube PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
