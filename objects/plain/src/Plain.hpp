/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plain
*/

#pragma once

#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Plain;
}

class Raytracer::Objects::Plain : public Raytracer::Common::IObject {
public:

    /**
     * @brief Construct a new Plain object
     * @param material Material of the plain
     * @param position Position of the plain
     * @param property Property of the plain
     */
    Plain(Common::Graphics::Material::Ptr material, const Common::Math::Point3D &position, const Common::ObjectProperty &property);
    
    /**
     * @brief Destroy the Plain object
     */
    ~Plain() override = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material::Ptr getMaterial() override;

private:
    /// @brief Material of the plain
    Common::Graphics::Material::Ptr _material;

    /// @brief Position of the plain
    const Common::Math::Point3D _position;

    /// @brief Radius of the plain
    Common::Math::Vector3D _normal; 
};
