/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

Raytracer::Objects::Sphere::Sphere()
{
}

Raytracer::Common::Math::HitInfo Raytracer::Objects::Sphere::computeCollision(const Raytracer::Common::Math::Ray &ray)
{
    Raytracer::Common::Math::HitInfo hitInfo;

    hitInfo.didHit = false;
    hitInfo.distance = 0;
    hitInfo.hitPoint = Raytracer::Common::Math::Point3D(0, 0, 0);
    hitInfo.normal = Raytracer::Common::Math::Vector3D(0, 0, 0);
    return hitInfo;
}
