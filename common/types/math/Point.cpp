/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point.cpp
*/

#include "Point.hpp"

using namespace Raytracer::Common;

std::ostream &operator<<(std::ostream &os, const Math::Point3D &point)
{
    os << "Point3D(" << point.x << ", " << point.y << ", " << point.z << ")";
    return os;
}

Math::Point3D::Point3D(float x, float y, float z) : Float3(x, y, z) {}

Math::Point3D::Point3D(const Math::Point3D &point): Point3D(point.x, point.y, point.z) {}

Math::Vector3D Math::Point3D::normalize() const
{
    return Math::Vector3D(x, y, z).normalize();
}

Math::Point3D operator+(const Math::Point3D &point1, const Math::Point3D &point2)
{
    return Math::Point3D(point1.x + point2.x, point1.y + point2.y, point1.z + point2.z);
}

Math::Point3D operator-(const Math::Point3D &point1, const Math::Point3D &point2)
{
    return Math::Point3D(point1.x - point2.x, point1.y - point2.y, point1.z - point2.z);
}

Math::Point2D::Point2D(float x, float y) : Float2(x, y) {}

Math::Point2D::Point2D(const Math::Point2D &point): Point2D(point.x, point.y) {}

std::ostream &operator<<(std::ostream &os, const Math::Point2D &point)
{
    os << "Point2D(" << point.x << ", " << point.y << ")";
    return os;
}

Math::Point2D operator+(const Math::Point2D &point1, const Math::Point2D &point2)
{
    return Math::Point2D(point1.x + point2.x, point1.y + point2.y);
}

Math::Point2D operator-(const Math::Point2D &point1, const Math::Point2D &point2)
{
    return Math::Point2D(point1.x - point2.x, point1.y - point2.y);
}
