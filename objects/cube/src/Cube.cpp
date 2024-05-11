/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cube
*/

#include <cmath>
#include <limits>
#include "Cube.hpp"

using namespace Raytracer::Objects;
using namespace Raytracer::Common;

const auto EPSILON = std::numeric_limits<float>::epsilon();

Cube::Cube(
    const std::string &name,
    Common::Graphics::Material::Ptr material,
    const Common::Math::Vector3D &rotation,
    const Common::Math::Point3D &position,
    const Common::ObjectProperty &property) :
    _name(name),
    _material(material),
    _rotation(rotation),
    _position(position)
{
    _size = std::get<Common::Math::Float3>(property);
    _radius = std::max(_size.x, std::max(_size.y, _size.z));
}

Math::HitInfo Cube::computeCollision(const Math::Ray &ray)
{
    Math::HitInfo hitInfo;

    return hitInfo;
}

Graphics::Material::Ptr Cube::getMaterial()
{
    return _material;
}
