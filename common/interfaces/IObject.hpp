/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Object
*/

#pragma once

#include "types/math/Ray.hpp"
#include "types/math/HitInfo.hpp"
#include "types/graphics/Material.hpp"

namespace Raytracer::Common {
    class IObject {
    public:
        /// @brief Default destructor
        virtual ~IObject() = default;

        /**
         * @brief Compute the collision of the object with a ray
         * @param ray Ray to compute the collision with
         * @return HitInfo containing the collision information
         */
        virtual Math::HitInfo computeCollision(const Math::Ray &ray) = 0;

        /**
         * @brief Get the Material object
         * @return Material of the object
         */
        virtual Graphics::Material getMaterial() = 0;
    };
}
