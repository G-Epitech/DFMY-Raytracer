/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#pragma once

#include "common/interfaces/IObject.hpp"

namespace Raytracer::Objects {
    class Sphere;
}

class Raytracer::Objects::Sphere : public Raytracer::Common::IObject {
public:
    /// @brief Default constructor
    Sphere(Raytracer::Common::Graphics::Material &material);
    /// @brief Default destructor
    ~Sphere() = default;

    /// @brief Get the HitInfo of the object
    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    /// @brief Get the Material of the object
    Common::Graphics::Material getMaterial() override;
private:
    Common::Graphics::Material _material;
};
