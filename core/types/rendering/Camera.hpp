/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.hpp
*/

#pragma once

#include <thread>

#include "Screen.hpp"
#include "interfaces/IObject.hpp"
#include "types/math/Vector.hpp"
#include "types/math/Point.hpp"

#define COMPUTE_THREADS 8

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

        /// @brief Segment of the screen
        typedef struct Segment {
            /// @brief Origin of the segment
            Common::Math::Size origin;
            /// @brief Size of the segment
            Common::Math::Size size;
            /// @brief Local screen size
            Common::Math::Float2 localScreenSize;
            /// @brief Local screen origin
            Common::Math::Point3D localScreenOrigin;
        } Segment;

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
        void compute(size_t threads, std::vector<Common::IObject::Ptr> &objects);

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
        /// @brief Vector of processing threads
        std::vector<std::thread> _threads;

    protected:
        /**
         * @brief Compute a segment of the screen
         * @param config Configuration of the segment
         * @param objects Objects to render
         */
        void _computeSegment(Segment config, std::vector<Common::IObject::Ptr> &objects);
    };
}
