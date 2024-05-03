/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IObjectProvider
*/

#pragma once

#include <memory>
#include "IObject.hpp"
#include "types/object/Manifest.hpp"
#include "types/graphics/Material.hpp"

namespace Raytracer::Common {
    class IObjectProvider {
    public:
        /// @brief Default destructor
        virtual ~IObjectProvider() = default;

        /**
         * @brief Create a new object
         * @param material Material of the object
         * @return Shared pointer to the new object 
         */
        virtual std::shared_ptr<IObject> create(const Graphics::Material &material, const Math::Point3D &position) = 0;

        /**
         * @brief Get the manifest of the object
         * @return Manifest of the object
         */
        virtual Object::Manifest getManifest() = 0;
    };
}
