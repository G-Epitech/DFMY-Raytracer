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

#define COMPUTE_THREADS 4

namespace Raytracer::Core::Rendering {
    class Camera {
    public:
        /// @brief Shared pointer to a camera
        typedef std::shared_ptr<Camera> Ptr;
        /// @brief Camera configuration
        typedef struct Config {
            /// @brief Name of the camera
            std::string name;
            /// @brief Screen configuration
            Screen::Config screen;
            /// @brief Camera position
            Common::Math::Point3D position;
            /// @brief Camera direction
            Common::Math::Vector3D direction;
            /// @brief Camera field of view
            float fov;
        } Config;

        class ComputeError : public exception {
        public:
            /**
             * @brief Create a error of compute
             * @param msg
             */
            explicit ComputeError(const std::string &msg = "unknown");

            /// @brief Default destructor
            ~ComputeError() override = default;

            /// @brief Get the message of the exception
            const char *what() const noexcept override;

        private:
            std::string _msg;
        };

        /**
         * @brief Create a new camera
         * @param config Configuration of the camera
         */
        explicit Camera(const Config &config);

        /// @brief Default constructor
        Camera() = delete;

        /// @brief Default destructor
        ~Camera() = default;

        /**
         * @brief Compute all pixels of the screen
         * @param threads Number of threads to use
         */
        void compute(size_t threads);

        /// @brief The position of the camera
        Common::Math::Point3D position;
        /// @brief The direction of the camera
        Common::Math::Vector3D direction;
        /// @brief The field of view of the camera
        float fov;
        /// @brief The screen of the camera
        Screen screen;
        /// @brief The name of the camera
        std::string name;
    };
}
