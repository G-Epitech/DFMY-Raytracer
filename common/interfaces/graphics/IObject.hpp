/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Object
*/

#pragma once

#include <memory>
#include "types/math/Ray.hpp"
#include "types/math/HitInfo.hpp"
#include "types/graphics/Material.hpp"

namespace Raytracer::Graphics {
    class IObject {
    public:
        /// @brief Alias for shared pointer to IObject
        typedef std::shared_ptr<IObject> Ptr;

        /// @brief Default destructor
        virtual ~IObject() = default;

        /// @brief Get the HitInfo of the object
        virtual Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) = 0;

        /// @brief Get the Material of the object
        virtual Common::Graphics::Material::Ptr getMaterial() = 0;
    };
}
