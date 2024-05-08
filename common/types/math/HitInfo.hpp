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
        /// @brief Emission strength of the hit
        float emissionStrength;
        /// @brief Emission color of the hit
        Graphics::Color emissionColor;
    } HitColor;

    /// @brief Represent an HitInfo between a ray and a shape
    typedef struct HitInfo {
        /// @brief Did the ray hit the shape
        bool didHit = false;
        /// @brief Distance between the ray and the shape
        float distance = 0;
        /// @brief Hit point
        Point3D hitPoint = Point3D(0, 0, 0);
        /// @brief Normal at the hit point
        Vector3D normal = Vector3D(0, 0, 0);
        /// @brief Color of the hit
        HitColor hitColor = {
            .color = Graphics::Color(0, 0, 0),
            .emissionStrength = 0,
            .emissionColor = Graphics::Color(0, 0, 0),
        };
    } HitInfo;
}
