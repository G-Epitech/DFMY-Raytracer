/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include <cmath>
#include <utility>
#include "Sphere.hpp"

#if defined(__linux__)
    #define COS facos
#elif defined(__APPLE__)
    #define COS acosf
#endif

Raytracer::Objects::Sphere::Sphere(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property)
        : _name(name),
        _material(std::move(material)),
        _rotation(rotation),
        _position(position)
{
    _radius = std::get<float>(property);
}

Raytracer::Common::Math::HitInfo Raytracer::Objects::Sphere::computeCollision(const Raytracer::Common::Math::Ray &ray)
{
    Common::Math::HitInfo hitInfo;
    Common::Math::Point3D offsetRayOrigin = ray.origin - _position;
    Common::Math::Vector3D oc(offsetRayOrigin.x, offsetRayOrigin.y, offsetRayOrigin.z);

    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - _radius * _radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hitInfo;

    float distance = (-b - sqrtf(discriminant)) / (2.0f * a);

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
            .emissionColor = _material->emissionColor,
            .reflectivity = _material->reflectivity,
    };

    for (auto &emission : _material->emissions) {
        auto angle = std::COS(emission.direction.normalize().dot(hitInfo.normal));
        if (angle < M_PI_2) {
            hitInfo.hitColor.emissionColor = emission.color;
            hitInfo.hitColor.emissionStrength = emission.strength;
        }
    }
    return hitInfo;
}

Raytracer::Common::Graphics::Material::Ptr Raytracer::Objects::Sphere::getMaterial()
{
    return _material;
}
