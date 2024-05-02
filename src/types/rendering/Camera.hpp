/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.hpp
*/

#pragma once

#include "Screen.hpp"
#include "types/math/Vector.hpp"
#include "types/math/Point.hpp"

namespace Rendering {
    class Camera {
    public:
        /**
         * @brief Create a new camera
         * @param screenSize Camera screen size
         * @param position Position of the camera
         * @param rotation Rotation of the camera
         * @param fov FOV of the camera
         */
        explicit Camera(
            const Screen::Size &size,
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            float fov
        );

        /// @brief Default constructor
        Camera() = delete;

        /// @brief Default destructor
        ~Camera() = default;

        /// @brief The position of the camera
        Math::Point3D position;
        /// @brief The rotation of the camera
        Math::Vector3D rotation;
        /// @brief The field of view of the camera
        float fov;
        /// @brief The screen of the camera
        Screen screen;
    };
}
