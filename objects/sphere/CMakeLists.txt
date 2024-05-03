# project(raytracer_sphere)
add_library(raytracer_sphere SHARED)

target_link_libraries(raytracer_sphere PRIVATE raytracer_common)

target_sources(raytracer_sphere PRIVATE
    export.cpp
    src/SphereProvider.hpp
    src/SphereProvider.cpp
    src/Sphere.hpp
    src/Sphere.cpp
)

target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
