## Source code library
add_library(libraytracer STATIC)
target_include_directories(libraytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

## Binary executable
add_executable(raytracer main.cpp)
target_link_libraries(raytracer libraytracer)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(libraytracer gcov)
endif()

## Add subdirectories
add_subdirectory(types)
add_subdirectory(interfaces)
