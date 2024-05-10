# Setup Raytracer Plane library
add_library(raytracer_plane SHARED)

# Link Raytracer Plane library
target_link_libraries(raytracer_plane PRIVATE raytracer_common)

# Add sources to Raytracer Plane library
target_sources(raytracer_plane PRIVATE
    export.cpp
    src/PlaneProvider.hpp
    src/PlaneProvider.cpp
    src/Plane.hpp
    src/Plane.cpp
)

# Include directories for Raytracer Plane library
target_include_directories(raytracer_plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(raytracer_plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
