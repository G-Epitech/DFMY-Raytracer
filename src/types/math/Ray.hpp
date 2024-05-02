/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#pragma once

#include "../math/Point.hpp"
#include "../math/Vector.hpp"

namespace Math {
    class Ray {
    public:
        /// @brief Create a new ray
        explicit Ray();
        /// @brief Create a new ray
        Ray(const Math::Point3D &origin, const Math::Vector3D &direction);
        /// @brief Default copy constructor
        Ray(const Ray &ray) = default;
        /// @brief Default destructor
        ~Ray() = default;

        /// @brief Origin of the ray
        Math::Point3D origin;
        /// @brief Direction of the ray
        Math::Vector3D direction;
    };
}
