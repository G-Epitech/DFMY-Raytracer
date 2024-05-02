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

namespace Graphics {
    class IObject {
    public:
        /// @brief Default destructor
        virtual ~IObject() = default;

        /// @brief Get the HitInfo of the object
        virtual Math::HitInfo computeCollision(const Math::Ray &ray) = 0;

        /// @brief Get the Material of the object
        virtual Material getMaterial() = 0;
    };
}
