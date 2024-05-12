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
                Common::Graphics::Material::Ptr material,
                const Common::Math::Vector3D &rotation,
                const Common::Math::Point3D &position);

            /**
             * @brief Destroy the Cube object
             */
            ~AObject() override = default;


            /// @brief Get the material associated to an object
            Graphics::Material::Ptr getMaterial() override;

        protected:
            /// @brief Name of the cube
            const std::string &_name;

            /// @brief Material of the cube
            Common::Graphics::Material::Ptr _material;

            /// @brief Position of the cube
            const Common::Math::Point3D _position;

            /// @brief Rotation of the cube
            Common::Math::Vector3D _rotation;
    };
}
