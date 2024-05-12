/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#pragma once

#include "common/abstracts/AObject.hpp"
#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Sphere;
}

class Raytracer::Objects::Sphere : public Raytracer::Common::AObject {
public:

    /**
     * @brief Construct a new Sphere object
     * @param name Name of the sphere
     * @param material Material of the sphere
     * @param rotation Rotation of the sphere
     * @param position Position of the sphere
     * @param property Property of the sphere
     */
    Sphere(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property);

    /**
     * @brief Destroy the Sphere object
     */
    ~Sphere() override = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    const std::string getType() noexcept override;

private:
    float _radius;
};
