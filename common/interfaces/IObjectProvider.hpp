/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IObjectProvider
*/

#pragma once

#include <libconfig.h++>
#include <variant>
#include <memory>
#include "IObject.hpp"
#include "types/object/Manifest.hpp"
#include "types/graphics/Material.hpp"

namespace Raytracer::Common {

    /// @brief Object property
    typedef struct {
        /// @brief Radius of the mesh
        float scale;
        /// @brief Path to the obj file to load
        std::string filename;
    } MeshProperty;

    /// @brief Variant of the possible object properties
    /// @details This variant is used to store the different properties of an object
    ///          It can be a float or a 3D float. For example, the radius of a sphere
    ///          is a float, and the size of a cube is a 3D float.
    typedef std::variant<float, Math::Float3, MeshProperty, Math::Vector3D> ObjectProperty;

    class IObjectProvider {
    public:
        /// @brief Shared pointer to the object provider
        typedef std::unique_ptr<IObjectProvider> Ptr;

        /// @brief Default destructor
        virtual ~IObjectProvider() = default;

        /**
         * @brief Create a new object
         * @param material Material of the object
         * @param rotation Rotation of the object
         * @param position Position of the object
         * @param property Property of the object
         * @return Created object
         */
        virtual IObject::Ptr create(const std::string &name,
            Common::Graphics::Material::Ptr material,
            const Common::Math::Vector3D &rotation,
            const Common::Math::Point3D &position,
            const Common::ObjectProperty &property
        ) = 0;

        /**
         * @brief Get the manifest of the object
         * @return Manifest of the object
         */
        virtual Object::Manifest getManifest() = 0;

        virtual Raytracer::Common::ObjectProperty parseProperty(const libconfig::Setting &setting) = 0;
    };
}
