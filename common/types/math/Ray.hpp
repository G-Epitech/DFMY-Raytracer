/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#pragma once

#include "Point.hpp"
#include "Vector.hpp"

namespace Raytracer::Common::Math {
    class Ray {
    public:
        /// @brief Create a new ray
        Ray();
        /// @brief Create a new ray
        explicit Ray(const Point3D &origin, const Vector3D &direction);
        /// @brief Default destructor
        ~Ray() = default;
        /// @brief Origin of the ray
        Point3D origin;
        /// @brief Direction of the ray
        Vector3D direction;
    };
}
