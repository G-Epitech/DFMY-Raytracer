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

        /**
         * @brief Rotate the point around the x axis
         * @param angle Angle to rotate
         * @return Rotated point
         */
        void rotateX(float angle);

        /**
         * @brief Rotate the point around the y axis
         * @param angle Angle to rotate
         * @return Rotated point
         */
        void rotateY(float angle);

        /**
         * @brief Rotate the point around the z axis
         * @param angle Angle to rotate
         * @return Rotated point
         */
        void rotateZ(float angle);

    };

    /// @brief Representing a 2D point
    class Point2D : public Float2 {
    public:

        /**
         * @brief Construct a new 2D point object
         * @param x Coordinate x
         * @param y Coordinate y
         */
        explicit Point2D(float x = 0, float y = 0);

        /**
         * @brief Construct a new 2D point object
         * @param point Point to copy
         */
        Point2D(const Point2D &point);

        /**
         * @brief Destroy the 2D point object
         */
        ~Point2D() = default;
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

/**
 * @brief Overload of the << operator
 * @param os Output stream
 * @param point Point to display
 * @return Output stream
 */
std::ostream &operator<<(std::ostream &os, const Raytracer::Common::Math::Point2D &point);

/**
 * @brief Overload of the + operator
 * @param point1 First point
 * @param point2 Second point
 * @return New point
 */
Raytracer::Common::Math::Point2D operator+(const Raytracer::Common::Math::Point2D &point1, const Raytracer::Common::Math::Point2D &point2);

/**
 * @brief Overload of the - operator
 * @param point1 First point
 * @param point2 Second point
 * @return New point
 */
Raytracer::Common::Math::Point2D operator-(const Raytracer::Common::Math::Point2D &point1, const Raytracer::Common::Math::Point2D &point2);
