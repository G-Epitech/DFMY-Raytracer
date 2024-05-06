/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** mesh
*/

#include <cmath>
#include "Mesh.hpp"

Raytracer::Objects::Mesh::Mesh(
    const Raytracer::Common::Graphics::Material::Ptr material,
    const Common::Math::Point3D &position,
    const Raytracer::Common::ObjectProperty &property) : _material(material), _position(position)
{
}

Raytracer::Common::Math::HitInfo Raytracer::Objects::Mesh::computeCollision(const Raytracer::Common::Math::Ray &ray)
{
    Common::Math::HitInfo hitInfo;

    return hitInfo;
}

Raytracer::Common::Graphics::Material::Ptr Raytracer::Objects::Mesh::getMaterial()
{
    return _material;
}
