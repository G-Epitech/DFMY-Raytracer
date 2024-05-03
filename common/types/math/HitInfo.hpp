/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Hit
*/

#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "types/graphics/Color.hpp"

namespace Raytracer::Common::Math {

    /// @brief Represent a color of a hit
    typedef struct HitColor {
        /// @brief Color of the hit
        Graphics::Color color;
        /// @brief Emission color of the hit
        float emissionStrength;
    } HitColor;

    /// @brief Represent an HitInfo between a ray and a shape
    typedef struct HitInfo {
        /// @brief Did the ray hit the shape
        bool didHit;
        /// @brief Distance between the ray and the shape
        float distance;
        /// @brief Hit point
        Point3D hitPoint;
        /// @brief Normal at the hit point
        Vector3D normal;
        /// @brief Color of the hit
        HitColor hitColor;
    } HitInfo;
}
