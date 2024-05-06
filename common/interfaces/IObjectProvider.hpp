/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IObjectProvider
*/

#pragma once

#include <variant>
#include <memory>
#include "IObject.hpp"
#include "types/object/Manifest.hpp"
#include "types/graphics/Material.hpp"

namespace Raytracer::Common {

    /// @brief Variant of the possible object properties
    /// @details This variant is used to store the different properties of an object
    ///          It can be a float or a 3D float. For example, the radius of a sphere
    ///          is a float, and the size of a cube is a 3D float.
    typedef std::variant<float, Math::Float3, std::string> ObjectProperty;

    class IObjectProvider {
    public:
        /// @brief Default destructor
        virtual ~IObjectProvider() = default;

        /**
         * @brief Create a new object
         * @param material Material of the object
         * @return Shared pointer to the new object 
         */
        virtual IObject::Ptr create(const Graphics::Material::Ptr material, const Math::Point3D &position, const ObjectProperty &property) = 0;

        /**
         * @brief Get the manifest of the object
         * @return Manifest of the object
         */
        virtual Object::Manifest getManifest() = 0;
    };
}
