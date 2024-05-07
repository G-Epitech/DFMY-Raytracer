# Setup Raytracer mesh library
add_library(raytracer_mesh SHARED)

# Link Raytracer mesh library
target_link_libraries(raytracer_mesh PRIVATE raytracer_common)

# Add sources to Raytracer mesh library
target_sources(raytracer_mesh PRIVATE
    export.cpp
    src/MeshProvider.hpp
    src/MeshProvider.cpp
    src/Mesh.hpp
    src/Mesh.cpp
    src/faces/QuadFace.hpp
    src/faces/QuadFace.cpp
    src/faces/TriFace.hpp
    src/faces/TriFace.cpp
)

# Include directories for Raytracer mesh library
target_include_directories(raytracer_mesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(raytracer_mesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
