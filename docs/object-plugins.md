![Baby gnu](https://upload.wikimedia.org/wikipedia/commons/4/42/Baby.gnu-800x800.png "Baby gnu")

# DFMY-Raytracer Object Plugins

A rendering engine should be extensible. One should be able to add new features without completely rewriting the code.

For every step of this documentation you can check the Sphere object

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

###### Object Fields

Each object has the following common fields:
- name (mainly used for GUI)
- material
- rotation
- origin/position
- **special property**

The special property is a field that's unique for each object.
Ex: radius for the sphere

------------

###### IObject Interface
This is the core of our object (see: `common/interfaces/IObject.hpp`).

In the object interface we will have multiple methods.
` virtual Math::HitInfo computeCollision(const Math::Ray &ray) = 0;`

This method is used by our raycasting system to know if a ray hit your object, so it can work out the reflections and pixels correctly. It is very important to correctly fill the `Math::HitInfo` structure correctly.

The interface also contains a method that returns the material associated to the object, also used by our raycasting system.

------------

###### IObjectProvider Interface
Seeing that each object plugin is a dynamic library we will need a provider. An instance of this provider will be returned in the entrypoint to the plugin (more on the entrypoint later).

A provider needs to have the following things:
- object creator
- manifest getter
- unique property parser

The **object creator** is just a method that takes in parameters the fields of an object and returns a shared pointer to the object it provides

The **manifest** is important, it contains the author of the plugin, the description, version, etc... But it also contains the name of the object, this is later used in the config.
So if the name of our object in the manifest is "Sphere" it also needs to be "Sphere" in the config. (see config docs).

Unique property parser, is used to parse the unique properties of the object. Here the libconfig++ is used. A lot of utils functions are available in the `common/config/ConfigUtils.hpp` file.
