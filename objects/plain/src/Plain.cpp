/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plain
*/

#include <cmath>
#include <limits>
#include "Plain.hpp"

using namespace Raytracer::Objects;
using namespace Raytracer::Common;

const auto EPSILON = std::numeric_limits<float>::epsilon();

Plain::Plain(
    const Graphics::Material::Ptr material,
    const Common::Math::Point3D &position,
    const ObjectProperty &property) : _material(material), _position(position)
{
    _normal = std::get<Math::Vector3D>(property);
}

Math::HitInfo Plain::computeCollision(const Math::Ray &ray)
{
    Common::Math::HitInfo hitInfo;

    float denom = ray.direction.dot(_normal);

    if (std::abs(denom) < EPSILON)
        return hitInfo;

    Math::Vector3D tv(
        _position.x - ray.origin.x,
        _position.y - ray.origin.y,
        _position.z - ray.origin.z
    );

    float t = (tv).dot(_normal) / denom;

    if (t < 0)
        return hitInfo;

    hitInfo.didHit = true;
    hitInfo.hitPoint.x = ray.origin.x + t * ray.direction.x;
    hitInfo.hitPoint.y = ray.origin.y + t * ray.direction.y;
    hitInfo.hitPoint.z = ray.origin.z + t * ray.direction.z;
    hitInfo.normal = _normal;
    hitInfo.distance = t;
    hitInfo.hitColor = {
        .color = _material->color,
        .emissionStrength = _material->emissionStrength,
        .emissionColor = _material->emissionColor
    };

    return hitInfo;
}

Graphics::Material::Ptr Plain::getMaterial()
{
    return _material;
}
