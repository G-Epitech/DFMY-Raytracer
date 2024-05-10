/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#pragma once

#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Sphere;
}

class Raytracer::Objects::Sphere : public Raytracer::Common::IObject {
public:

    /**
     * @brief Construct a new Sphere object
     * @param material Material of the sphere
     * @param position Position of the sphere
     * @param property Property of the sphere
     */
    Sphere(Common::Graphics::Material::Ptr  material, const Common::Math::Point3D &position, const Common::ObjectProperty &property);

    /**
     * @brief Destroy the Sphere object
     */
    ~Sphere() override = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material::Ptr getMaterial() override;

private:
    Common::Graphics::Material::Ptr _material;
    const Common::Math::Point3D _position;
    float _radius;
};
