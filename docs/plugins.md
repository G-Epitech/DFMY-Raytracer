![Baby gnu](https://upload.wikimedia.org/wikipedia/commons/4/42/Baby.gnu-800x800.png "Baby gnu")

# DFMY-Raytracer Plugins

A rendering engine should be extensible. One should be able to add new features without completely rewriting the code.

For every step of this documentation 

### Build
All of the object plugins are found in the `objects` folder, in the folder we have a CMake that will be automatically called by the CMake at the root that looks like this:
````
# Set the shared library prefix to an empty string
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Add the subdirectories
````

Basically here you will add the subdirectory of your object plugin with the name of your object.
For example:
```
add_subdirectory(sphere)
```

Now in your sphere subdirectory, you need to create your own CMake that will build your plugin, it should look like this:
```
# Setup Raytracer Sphere library
add_library(raytracer_sphere SHARED)

# Link Raytracer Sphere library
target_link_libraries(raytracer_sphere PRIVATE raytracer_common)

# Add sources to Raytracer Sphere library
target_sources(raytracer_sphere PRIVATE
    export.cpp
    src/SphereProvider.hpp
    src/SphereProvider.cpp
    src/Sphere.hpp
    src/Sphere.cpp
)

# Include directories for Raytracer Sphere library
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(raytracer_sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
```

You will put all of your files in the `tareget_sources` section. And we will go over each file later in this documentation.

### Architecture
Every object plugin has a specific architecture, they each need to follow a certain inheritance tree, to be compatible with the rest of the Raytracer.


------------


###### IObject Interface
This is the core of our object (see: `common/interfaces/IObject.hpp`).

In the object interface we will have multiple methods.
` virtual Math::HitInfo computeCollision(const Math::Ray &ray) = 0;`

This method is used by our raycasting system to know if a ray hit your object, so it can work out the reflections and pixels correctly. It is very important to correctly fill the `Math::HitInfo` structure correctly.
