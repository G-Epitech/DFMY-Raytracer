/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include <cmath>
#include "Sphere.hpp"

Raytracer::Objects::Sphere::Sphere(
    const Raytracer::Common::Graphics::Material::Ptr material,
    const Common::Math::Point3D &position,
    const Raytracer::Common::ObjectProperty &property) : _material(material), _position(position)
{
    _radius = std::get<float>(property);
}

Raytracer::Common::Math::HitInfo Raytracer::Objects::Sphere::computeCollision(const Raytracer::Common::Math::Ray &ray)
{
    Common::Math::HitInfo hitInfo;
    Common::Math::Point3D offsetRayOrigin = ray.origin - _position;
    Common::Math::Vector3D oc(offsetRayOrigin.x, offsetRayOrigin.y, offsetRayOrigin.z);

    float a = ray.direction.dot(ray.direction);
    float b = 2.0 * oc.dot(ray.direction);
    float c = oc.dot(oc) - _radius * _radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hitInfo;

    float distance = (-b - sqrt(discriminant)) / (2.0 * a);

    if (distance < 0)
        return hitInfo;

    hitInfo.didHit = true;
    hitInfo.distance = distance;
    auto intersectionNormal = ray.direction * distance;
    Common::Math::Point3D hitPointData(intersectionNormal.x, intersectionNormal.y, intersectionNormal.z);
    hitInfo.hitPoint = ray.origin + hitPointData;
    hitInfo.normal = (hitInfo.hitPoint - _position).normalize();
    hitInfo.hitColor = {
        .color = _material->color,
        .emissionStrength = _material->emissionStrength,
        .emissionColor = _material->emissionColor
    };
    return hitInfo;
}

Raytracer::Common::Graphics::Material::Ptr Raytracer::Objects::Sphere::getMaterial()
{
    return _material;
}
