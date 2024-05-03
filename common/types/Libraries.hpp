/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Libraries
*/

#pragma once

#include "interfaces/IObjectProvider.hpp"

#define OBJECT_PROVIDER_GETTER_NAME getObjectProvider
#define OBJECT_TYPE_GETTER_NAME getObjectType
#define STRINGIFY(x) #x
#define SHARED_STRINGIFY(x) STRINGIFY(x)

namespace Raytracer::Common {

    /// @brief Enum representing the type of an object
    typedef enum {
        /// @brief Sphere object
        SPHERE = 0,
        /// @brief Plane object
        PLANE = 1,
        /// @brief Cube object
        CUBE = 2,
        /// @brief Cylinder object
        CYLINDER = 3,
        /// @brief Cone object
        CONE = 4,
        /// @brief Torus object
        TORUS = 5,
        /// @brief Triangle object
        TRIANGLE = 6,
        /// @brief Mesh object
        MESH = 7,
        /// @brief Unknown object
        UNKNOWN = 8
    } ObjectType;

    /// @brief Function pointer to get an object provider
    typedef IObjectProvider* (*ObjectProviderGetter)(void);

    /// @brief Function pointer to get an object type
    typedef ObjectType (*ObjectTypeGetter)(void);
}
