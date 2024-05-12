target_sources(raytracer_core PRIVATE
        Handler.cpp
        Handler.cpp
        GuiContext.hpp
        TGui.cpp
        TGui.hpp
)
add_subdirectory(components)
add_subdirectory(widgets)
