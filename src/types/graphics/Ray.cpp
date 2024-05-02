/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

Graphics::Ray::Ray()
{
    origin = Math::Point3D();
    direction = Math::Vector3D();
}

Graphics::Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
{
    this->origin = origin;
    this->direction = direction;
}
