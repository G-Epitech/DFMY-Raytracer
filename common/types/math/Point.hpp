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

        /**
         * @brief Construct a new 3D point object
         * @param x Coordinate x
         * @param y Coordinate y
         * @param z Coordinate z
         */
        explicit Point3D(float x = 0, float y = 0, float z = 0);

        /**
         * @brief Construct a new 3D point object
         * @param point Point to copy
         */
        Point3D(const Point3D &point);

        /**
         * @brief Destroy the 3D point object
         */
        ~Point3D() = default;

        /**
         * @brief Get the distance between two points
         * @param point Point to calculate the distance with
         * @return Distance between the two points
         */
        Common::Math::Vector3D normalize() const;
    };
}

/**
 * @brief Overload of the << operator
 * @param os Output stream
 * @param point Point to display
 * @return Output stream
 */
std::ostream &operator<<(std::ostream &os, const Raytracer::Common::Math::Point3D &point);

/**
 * @brief Overload of the + operator
 * @param point1 First point
 * @param point2 Second point
 * @return New point
 */
Raytracer::Common::Math::Point3D operator+(const Raytracer::Common::Math::Point3D &point1, const Raytracer::Common::Math::Point3D &point2);

/**
 * @brief Overload of the - operator
 * @param point1 First point
 * @param point2 Second point
 * @return New point
 */
Raytracer::Common::Math::Point3D operator-(const Raytracer::Common::Math::Point3D &point1, const Raytracer::Common::Math::Point3D &point2);
