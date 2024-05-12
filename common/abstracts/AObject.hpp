/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** AObject
*/

#pragma once

#include "types/math/Ray.hpp"
#include "types/math/HitInfo.hpp"
#include "types/graphics/Material.hpp"
#include "interfaces/IObject.hpp"

namespace Raytracer::Common {
    class AObject : public IObject {
        public:
            /**
             * @brief Construct a new Cube object
             * @param name Name of the cube
             * @param material Material of the cube
             * @param rotation Rotation of the cube
             * @param position Position of the cube
             */
            AObject(
                const std::string &name,
                Graphics::Material::Ptr material,
                const Math::Vector3D &rotation,
                const Math::Point3D &position);

            /**
             * @brief Destroy the Cube object
             */
            ~AObject() override = default;


            /// @brief Get the material associated to an object
            Graphics::Material::Ptr getMaterial() override;

            /// @brief Get the name of the object
            std::string &getName() noexcept override;

            /// @brief Get the position of the object
            Math::Point3D &getPosition() noexcept override;

            /// @brief Get the rotation of the object
            Math::Vector3D &getRotation() noexcept override;
        protected:
            /// @brief Name of the cube
            std::string _name;

            /// @brief Material of the cube
            Graphics::Material::Ptr _material;

            /// @brief Position of the cube
            Math::Point3D _position;

            /// @brief Rotation of the cube
            Math::Vector3D _rotation;
    };
}
