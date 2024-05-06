/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector.hpp
*/

#pragma once

#include <iostream>
#include "Float.hpp"

namespace Raytracer::Common::Math {
    class Vector2D: public Float2 {
    public:
        /// @brief Default constructor
        explicit Vector2D(float x = 0, float y = 0);

        /// @brief Copy constructor
        Vector2D(const Vector2D &vector);

        /// @brief Default destructor
        ~Vector2D() = default;

        /**
         * @brief Add two vectors
         * @param other Other vector to add
         * @return Computed vector
         */
        Vector2D operator+(const Vector2D &other) const;

        /**
         * @brief Add an other vector to the current vector
         * @param other Other vector to add
         * @return Reference to the current vector
         */
        Vector2D &operator+=(const Vector2D &other);

        /**
         * @brief Subtract two vectors
         * @param other Other vector to subtract
         * @return Computed vector
         */
        Vector2D operator-(const Vector2D &other) const;

        /**
         * @brief Subtract an other vector to the current vector
         * @param other Other vector to subtract
         * @return Reference to the current vector
         */
        Vector2D &operator-=(const Vector2D &other);

        /**
         * @brief Multiply two vectors
         * @param other Other vector to multiply
         * @return Computed vector
         */
        Vector2D operator*(const Vector2D &other) const;

        /**
         * @brief Multiply a vector by a coefficient
         * @param c Coefficient to multiply the vector by
         * @return Computed vector
         */
        Vector2D operator*(float c) const;

        /**
         * @brief Multiply the current vector by an other vector
         * @param other Other vector to multiply
         * @return Reference to the current vector
         */
        Vector2D &operator*=(const Vector2D &other);

        /**
         * @brief Multiply the current vector by a coefficient
         * @param c Coefficient to multiply the vector by
         * @return Reference to the current vector
         */
        Vector2D &operator*=(float c);

        /**
         * @brief Divide a vector by a coefficient
         * @param c Coefficient to divide the vector by
         * @return Computed vector
         */
        Vector2D operator/(float c) const;

        /**
         * @brief Divide the current vector by an other vector
         * @param c Coefficient to divide the vector by
         * @return Reference to the current vector
         */
        Vector2D &operator/=(float c);

        /**
         * @brief Compute cross product of given vector
         * @return Computed cross product
         */
        [[nodiscard]]
        float length() const;
    };

    class Vector3D : public Float3 {
    public:
        /// @brief Default constructor
        explicit Vector3D(float x = 0, float y = 0, float z = 0);

        /// @brief Copy constructor
        Vector3D(const Vector3D &vector);

        /// @brief Default destructor
        ~Vector3D() = default;

        /**
         * @brief Add two vectors
         * @param other Other vector to add
         * @return Computed vector
         */
        Vector3D operator+(const Vector3D &other) const;

        /**
         * @brief Add an other vector to the current vector
         * @param other Other vector to add
         * @return Reference to the current vector
         */
        Vector3D &operator+=(const Vector3D &other);

        /**
         * @brief Subtract two vectors
         * @param other Other vector to subtract
         * @return Computed vector
         */
        Vector3D operator-(const Vector3D &other) const;

        /**
         * @brief Subtract an other vector to the current vector
         * @param other Other vector to subtract
         * @return Reference to the current vector
         */
        Vector3D &operator-=(const Vector3D &other);

        /**
         * @brief Multiply two vectors
         * @param other Other vector to multiply
         * @return Computed vector
         */
        Vector3D operator*(const Vector3D &other) const;

        /**
         * @brief Multiply a vector by a coefficient
         * @param c Coefficient to multiply the vector by
         * @return Computed vector
         */
        Vector3D operator*(float c) const;

        /**
         * @brief Multiply the current vector by an other vector
         * @param other Other vector to multiply
         * @return Reference to the current vector
         */
        Vector3D &operator*=(const Vector3D &other);

        /**
         * @brief Multiply the current vector by a coefficient
         * @param c Coefficient to multiply the vector by
         * @return Reference to the current vector
         */
        Vector3D &operator*=(float c);

        /**
         * @brief Divide a vector by a coefficient
         * @param c Coefficient to divide the vector by
         * @return Computed vector
         */
        Vector3D operator/(float c) const;

        /**
         * @brief Divide the current vector by an other vector
         * @param c Coefficient to divide the vector by
         * @return Reference to the current vector
         */
        Vector3D &operator/=(float c);

        /**
         * @brief Compute scalar product of given vector
         * @return Computed scalar product
         */
        [[nodiscard]]
        float dot(const Vector3D &other) const;

        /**
         * @brief Compute cross product of given vector
         * @param other Other vector to compute cross product with
         * @return Computed cross product
         */
        [[nodiscard]]
        Vector3D cross(const Vector3D &other) const;

        /**
         * @brief Compute cross product of given vector
         * @return Computed cross product
         */
        [[nodiscard]]
        float length() const;

        /**
         * @brief Normalize the vector
         * @return Normalized vector
         */
        [[nodiscard]]
        Vector3D normalize() const;
    };
}

/**
 * @brief Overload of the << operator
 * @param os Output stream
 * @param v Vector to display
 * @return Output stream
 */
std::ostream &operator<<(std::ostream &os, const Raytracer::Common::Math::Vector3D &v);
