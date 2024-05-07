/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IFace
*/

#pragma once

#include "common/types/math/Ray.hpp"
#include "common/types/math/HitInfo.hpp"

namespace Raytracer::Objects::MeshFaces {
    class IFace {
    public:

        /**
         * @brief Destroy the IFace object
         */
        virtual ~IFace() = default;

        /**
         * @brief Compute the collision of the face
         * @param ray Ray to compute the collision
         * @return HitInfo
         */
        virtual Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) = 0;
    };
}