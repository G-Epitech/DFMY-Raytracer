/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Hit
*/

#pragma once

#include "../math/Point.hpp"
#include "../math/Vector.hpp"

namespace Graphics {
    /// @brief Represent an HitInfo between a ray and a shape
    typedef struct HitInfo {
        /// @brief Create a new HitInfo, black by default
        HitInfo();
        /// @brief Create a new HitInfo from another HitInfo
        HitInfo(const HitInfo &HitInfo) = default;
        /// @brief Did the ray hit the shape
        bool didHit;
        /// @brief Distance between the ray and the shape
        float distance;
        /// @brief Hit point
        Math::Point3D hitPoint;
        /// @brief Normal at the hit point
        Math::Vector3D normal;
    } HitInfo;
}
