![Baby gnu](https://upload.wikimedia.org/wikipedia/commons/4/42/Baby.gnu-800x800.png "Baby gnu")


# DFMY Scene Configuration

This guide will walk you through creating your own configuration file for a raytracing scene. The configuration file defines various parameters such as ambient lighting, camera settings, materials, and objects in the scene.

1. [Getting Started](#getting-started)
2. [Configuration Structure](#configuration-structure)
    - [Ambient Lighting](#ambient-lighting)
    - [Cameras](#cameras)
    - [Materials](#materials)
        - [Possible Errors](#possible-errors)
        - [Emissions](#emissions)
    - [Objects](#objects)
3. [Example Configuration](#example-configuration)

## Getting Started

Before creating your configuration file, make sure you have a clear understanding of the scene you want to create. This includes the desired lighting, camera placement, materials, and objects.

## Configuration Structure

The configuration file follows a structured format with sections for different components of the scene. Here's an overview of each section:

### Ambient Lighting

Defines the ambient lighting in the scene.

```plaintext
ambient = {
    color = {r=RED_VALUE, g=GREEN_VALUE, b=BLUE_VALUE, a=ALPHA_VALUE}
    strength = STRENGTH_VALUE
}
```

- `color`: Specifies the color of the ambient light in RGBA format.
- `strength`: Specifies the strength of the ambient light.

### Cameras

Defines the cameras in the scene.

```plaintext
cameras = (
    {
        name = "CAMERA_NAME",
        size = {width=WIDTH_VALUE, height=HEIGHT_VALUE},
        position = {x=X_POSITION, y=Y_POSITION, z=Z_POSITION},
        direction = {x=X_DIRECTION, y=Y_DIRECTION, z=Z_DIRECTION},
        fieldOfView = FIELD_OF_VIEW_VALUE,
    }
)
```

- `name`: Specifies the name of the camera. ("string")
- `size`: Specifies the size of the camera viewport. (both are ints)
- `position`: Specifies the position of the camera in 3D space. (all are floats)
- `direction`: Specifies the direction the camera is facing. (all are floats)
- `fieldOfView`: Specifies the field of view of the camera. (float)

!! The `fieldOfView` needs to be between 0 and 180. Everything else is considered an error.

### Materials

Defines the materials used for objects in the scene.

```plaintext
materials = (
    {
        name = "MATERIAL_NAME",
        objectColor = {r=RED_VALUE, g=GREEN_VALUE, b=BLUE_VALUE, a=ALPHA_VALUE},
        emissions = (),
        reflectivity = REFLECTIVITY_VALUE,
        emissionStrength = EMISSION_STRENGTH_VALUE,
        emissionColor = {r=RED_VALUE, g=GREEN_VALUE, b=BLUE_VALUE, a=ALPHA_VALUE}
    },
    ...
)
```

- `name`: Specifies the name of the material. (string)
- `objectColor`: Specifies the color of the material in RGBA format. (all floats)
- `reflectivity`: Specifies the reflectivity of the material. (float)
- `emissionStrength`: Specifies the strength of emission from the material. (float)
- `emissionColor`: Specifies the color of emission from the material in RGBA format. (all floats)

#### Possible Errors
- Multiple materials with the same name
- Reflectivity needs to be between 0 and 1

#### Emissions
Emissions are a special field where can define multiple emissions from a same object, here is an example:
```
       emissions = (
          {
             direction = {x=0.0, y=-1.0, z=0.0},
             color = {r=255, g=0, b=0, a=255},
             strength = 1.0
          },
          {
            direction = {x=1.0, y=0.0, z=0.0},
            color = {r=0, g=255, b=0, a=255},
            strength = 1.0
          },
          {
            direction = {x=-1.0, y=0.0, z=0.0},
            color = {r=0, g=0, b=255, a=255},
            strength = 1.0
          }
       ),
```

These are like rays of light that will each have their own color, strength and direction

### Objects

Defines the objects present in the scene.

```plaintext
objects = (
    {
        name = "OBJECT_NAME",
        type = "OBJECT_TYPE",
        material = "MATERIAL_NAME",
        origin = {x=X_ORIGIN, y=Y_ORIGIN, z=Z_ORIGIN},
        rotation= {x=X_ROTATION, y=Y_ROTATION, z=Z_ROTATION},
        properties = {
            radius = RADIUS_VALUE
        }
    },
)
```

- `name`: Specifies the name of the object. (string)
- `type`: Specifies the type of the object (e.g., sphere, cube, etc.). (string)
- `material`: Specifies the material applied to the object. (string)
- `origin`: Specifies the origin point of the object in 3D space. (all floats)
- `rotation`: Specifies the rotation of the object.  (all floats)
- `properties`: Specifies additional properties of the object (e.g., radius for a sphere). (depends on the object).

## Example Configuration

Here's an example configuration file for reference:

```plaintext
scenes/sample.cfg
```