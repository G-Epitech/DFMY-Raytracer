# Setup Raytracer Sphere library
add_library(raytracer_sphere SHARED)

# Link Raytracer Sphere library
target_link_libraries(raytracer_sphere PRIVATE raytracer_common)

# Add sources to Raytracer Sphere library
target_sources(raytracer_sphere PRIVATE
    export.cpp
    src/SphereProvider.hpp
    src/SphereProvider.cpp
    src/Sphere.hpp
    src/Sphere.cpp
)

# Include directories for Raytracer Sphere library
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
