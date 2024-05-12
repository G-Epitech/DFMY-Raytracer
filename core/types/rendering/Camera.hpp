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

#define COMPUTE_THREADS 50

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

        /// @brief Parameters of camera computing
        struct ComputeParams {
            /// @brief Number of threads to use
            size_t threads;
            /// @brief Additional frames to render
            size_t additionalFrames;
            /// @brief Rays per pixel
            size_t raysPerPixel;
            /// @brief Ray bounce limit
            size_t rayBounceLimit;
        };

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
            [[nodiscard]]
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
         * @param params Parameters of the computing
         * @param objects Objects to compute
         */
        void compute(const ComputeParams &params, std::vector<Common::IObject::Ptr> &objects);

        /**
         * @brief Get the status of the computation
         * @return Status of the computation
         */
        [[nodiscard]]
        float getComputeStatus() const;

        /**
         * @brief Cancel the computation
         */
        void cancelCompute();

        /**
         * @brief Wait for the threads to teardown
         */
        void waitThreadsTeardown();

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
        /// @brief Number of processed pixels
        size_t _processedPixels = 0;

        /// @brief Mutex of the status
        std::mutex _statusMutex;

        /**
         * @brief Compute a segment of the screen
         * @param params Parameters of the computing
         * @param config Configuration of the segment
         * @param objects Objects to compute
         */
        void _computeSegment(const ComputeParams &params, Segment config, std::vector<Common::IObject::Ptr> &objects);

        /**
         * @brief Compute a frame of the screen
         * @param config Configuration of the frame
         * @param objects Objects to compute
         * @param x X position of the pixel
         * @param y Y position of the pixel
         * @param raysPerPixels Number of rays per pixel
         * @param bounce Number of bounces
         * @return Color of the frame
         */
        Common::Graphics::Color
        _computeFrame(Segment config, std::vector<Common::IObject::Ptr> &objects, size_t x, size_t y,
                      size_t raysPerPixels, size_t bounce);

        /**
         * @brief Compute the collision of a ray with the objects
         * @param ray Ray to compute
         * @param objects Objects to compute
         * @return HitInfo of the collision
         */
        Common::Math::HitInfo
        _computeRayCollision(const Common::Math::Ray &ray, std::vector<Common::IObject::Ptr> &objects);

        /**
         * @brief Get the incoming light of a ray
         * @param ray Ray to compute
         * @param rngState Random state
         * @param objects Objects to compute
         * @param bounce Number of bounces
         * @return Incoming light of the ray
         */
        Common::Graphics::Color _getIncomingLight(Common::Math::Ray ray, unsigned int rngState,
                                                  std::vector<Common::IObject::Ptr> &objects, size_t bounce);

        /**
         * @brief Get a random direction (hemisphere) from a normal
         * @param normal Vector normal of the direction
         * @param rngState Random state
         * @return Random direction
         */
        Common::Math::Vector3D _getRandomDirection(Common::Math::Vector3D &normal, unsigned int &rngState);

        static Common::Graphics::Color _getEnvironmentLight(Common::Math::Ray &ray);

        static float _smoothStep(float edge0, float edge1, float x);

        static Common::Graphics::Color _lErp(const Common::Graphics::Color &a, const Common::Graphics::Color &b,
                                             float t);
    };
}
