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
    /// @brief Default constructor
    Sphere(const Common::Graphics::Material &material, const Common::Math::Point3D &position, const Common::ObjectProperty &property);
    /// @brief Default destructor
    ~Sphere() = default;

    void setRadius(float radius);

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material getMaterial() override;

private:
    const Common::Graphics::Material _material;
    const Common::Math::Point3D _position;
    float _radius;
};
