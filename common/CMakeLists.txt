# Source code library
add_library(raytracer_common STATIC)
target_include_directories(raytracer_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(raytracer_common gcov)
endif()

# Add subdirectories
add_subdirectory(types)
add_subdirectory(interfaces)
