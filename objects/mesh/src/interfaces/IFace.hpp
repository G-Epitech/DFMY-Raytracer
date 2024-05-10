/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IFace
*/

#pragma once

#include "common/types/math/Ray.hpp"
#include "common/types/math/HitInfo.hpp"

using namespace Raytracer::Common::Math;

namespace Raytracer::Objects::MeshFaces {
    /// @brief Representing a face
    class IFace {
    public:

        /**
         * @brief Destroy the IFace object
         */
        virtual ~IFace() = default;

        /**
         * @brief Compute the collision of the face
         * @param ray Ray to compute the collision
         * @param hitInfo Hit info to fill
         * @return HitInfo
         */
        virtual void computeCollision(const Ray &ray, HitInfo &hitInfo) = 0;
    };
}