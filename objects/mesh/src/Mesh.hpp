/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** mesh
*/

#pragma once

#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Mesh;
}

class Raytracer::Objects::Mesh : public Raytracer::Common::IObject {
public:

    /**
     * @brief Construct a new mesh object
     * @param material Material of the mesh
     * @param position Position of the mesh
     * @param property Property of the mesh
     */
    Mesh(const Common::Graphics::Material::Ptr material, const Common::Math::Point3D &position, const Common::ObjectProperty &property);

    /**
     * @brief Destroy the mesh object
     */
    ~Mesh() = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material::Ptr getMaterial() override;

private:
    Common::Graphics::Material::Ptr _material;
    const Common::Math::Point3D _position;
    float _radius;
};
