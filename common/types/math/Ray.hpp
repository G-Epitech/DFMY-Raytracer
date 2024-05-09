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

        /**
         * @brief Construct a new Ray object
         */
        Ray();
        
        /**
         * @brief Construct a new Ray object
         * @param origin Origin of the ray
         * @param direction Direction of the ray
         */
        explicit Ray(const Point3D &origin, const Vector3D &direction);
        
        /**
         * @brief Destroy the Ray object
         */
        ~Ray();

        /// @brief Origin of the ray
        Point3D origin;
        /// @brief Direction of the ray
        Vector3D direction;
    };
}
