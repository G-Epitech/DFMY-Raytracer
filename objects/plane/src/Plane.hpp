/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#pragma once

#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Plane;
}

class Raytracer::Objects::Plane : public Raytracer::Common::IObject {
public:

    /**
     * @brief Construct a new Plane object
     * @param name Name of the plane
     * @param material Material of the plane
     * @param rotation Rotation of the plane
     * @param position Position of the plane
     * @param property Property of the plane
     */
    Plane(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property);
    
    /**
     * @brief Destroy the Plane object
     */
    ~Plane() override = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material::Ptr getMaterial() override;

private:
    /// @brief Name of the plane
    const std::string &_name;

    /// @brief Material of the plane
    Common::Graphics::Material::Ptr _material;

    /// @brief Position of the plane
    const Common::Math::Point3D _position;

    /// @brief Rotation of the plane
    Common::Math::Vector3D _rotation;

    /// @brief Radius of the plane
    Common::Math::Vector3D _normal;
};
