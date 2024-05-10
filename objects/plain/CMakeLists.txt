# Setup Raytracer Plain library
add_library(raytracer_plain SHARED)

# Link Raytracer Plain library
target_link_libraries(raytracer_plain PRIVATE raytracer_common)

# Add sources to Raytracer Plain library
target_sources(raytracer_plain PRIVATE
    export.cpp
    src/PlainProvider.hpp
    src/PlainProvider.cpp
    src/Plain.hpp
    src/Plain.cpp
)

# Include directories for Raytracer Plain library
target_include_directories(raytracer_plain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(raytracer_plain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
