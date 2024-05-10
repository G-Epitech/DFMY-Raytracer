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
     * @param material Material of the plane
     * @param position Position of the plane
     * @param property Property of the plane
     */
    Plane(Common::Graphics::Material::Ptr material, const Common::Math::Point3D &position, const Common::ObjectProperty &property);
    
    /**
     * @brief Destroy the Plane object
     */
    ~Plane() override = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material::Ptr getMaterial() override;

private:
    /// @brief Material of the plane
    Common::Graphics::Material::Ptr _material;

    /// @brief Position of the plane
    const Common::Math::Point3D _position;

    /// @brief Radius of the plane
    Common::Math::Vector3D _normal; 
};
