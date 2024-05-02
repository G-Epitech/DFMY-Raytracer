## Source code library
add_library(raytracer-common STATIC)
target_include_directories(raytracer-common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(raytracer-common gcov)
endif()

## Add subdirectories
add_subdirectory(types)
add_subdirectory(interfaces)
