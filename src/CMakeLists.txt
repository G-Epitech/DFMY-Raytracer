## Source code library
add_library(libraytracer STATIC)

## Binary executable
add_executable(raytracer main.cpp)
target_link_libraries(raytracer libraytracer)
target_link_libraries(raytracer config++)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(libraytracer gcov)
endif()

## Add subdirectories
add_subdirectory(types)
add_subdirectory(interfaces)
add_subdirectory(config)
