/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point.cpp
*/

#include "Point.hpp"

std::ostream &operator<<(std::ostream &os, const Math::Point3D &point)
{
    os << "Point3D(" << point.x << ", " << point.y << ", " << point.z << ")";
    return os;
}

Math::Point3D::Point3D(float x, float y, float z) : Float3(x, y, z) {}

Math::Point3D::Point3D(const Math::Point3D &point): Point3D(point.x, point.y, point.z) {}
