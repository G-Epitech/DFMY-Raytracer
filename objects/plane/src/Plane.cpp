/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#include <cmath>
#include <limits>
#include "Plane.hpp"

using namespace Raytracer::Objects;
using namespace Raytracer::Common;

const auto EPSILON = std::numeric_limits<float>::epsilon();

Plane::Plane(
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
    _normal = std::get<Math::Vector3D>(property);
    _normal = _normal.normalize();
}

Math::HitInfo Plane::computeCollision(const Math::Ray &ray)
{
    Common::Math::HitInfo hitInfo;
    auto rayOrigin = ray.origin;

    rayOrigin.z += 0.0001f;

    auto rayDirection = ray.direction.normalize();

    float denom = _normal.dot(rayDirection);

    if (std::abs(denom) > EPSILON) {

        Common::Math::Vector3D p0l0(
            _position.x - rayOrigin.x,
            _position.y - rayOrigin.y,
            _position.z - rayOrigin.z
        );
        float t = p0l0.dot(_normal) / denom;

        if (t > 0) {
            hitInfo.didHit = true;
            hitInfo.distance = t;
            hitInfo.hitPoint.x = rayOrigin.x + t * rayDirection.x;
            hitInfo.hitPoint.y = rayOrigin.y + t * rayDirection.y;
            hitInfo.hitPoint.z = rayOrigin.z + t * rayDirection.z;
            hitInfo.normal = _normal;
            hitInfo.hitColor = {
                .color = _material->color,
                .emissionStrength = _material->emissionStrength,
                .emissionColor = _material->emissionColor
            };
        }
    }

    return hitInfo;
}

Graphics::Material::Ptr Plane::getMaterial()
{
    return _material;
}
