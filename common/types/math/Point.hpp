/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point.hpp
*/

#pragma once

#include <iostream>
#include "Float.hpp"
#include "Vector.hpp"

namespace Raytracer::Common::Math {
    /// @brief Representing a 3D point
    class Point3D : public Float3 {
    public:
        explicit Point3D(float x = 0, float y = 0, float z = 0);
        Point3D(const Point3D &point);
        ~Point3D() = default;
        Common::Math::Vector3D normalize() const;
    };
}

std::ostream &operator<<(std::ostream &os, const Raytracer::Common::Math::Point3D &point);
Raytracer::Common::Math::Point3D operator+(const Raytracer::Common::Math::Point3D &point1, const Raytracer::Common::Math::Point3D &point2);
Raytracer::Common::Math::Point3D operator-(const Raytracer::Common::Math::Point3D &point1, const Raytracer::Common::Math::Point3D &point2);
