include_directories(../../src)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include(GoogleTest)
enable_testing()
add_executable(raytracer_tests main.cpp)

# Subdirectories
add_subdirectory(types)

gtest_discover_tests(raytracer_tests)
target_link_libraries(raytracer_tests libraytracer gtest gtest_main)
