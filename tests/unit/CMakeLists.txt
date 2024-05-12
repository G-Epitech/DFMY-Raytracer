include_directories(${PROJECT_SOURCE_DIR}/core)
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include(GoogleTest)
enable_testing()
add_executable(raytracer_tests main.cpp)

# Subdirectories
add_subdirectory(core)
add_subdirectory(common)

gtest_discover_tests(raytracer_tests)
target_link_libraries(raytracer_tests
        raytracer_core
        raytracer_common
        gtest
        gtest_main
)
