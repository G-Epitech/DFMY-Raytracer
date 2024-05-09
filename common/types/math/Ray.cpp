/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

using namespace Raytracer::Common;

Math::Ray::Ray() = default;

Math::Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
{
    this->origin = origin;
    this->direction = direction;
}

Math::Ray::~Ray() = default;
