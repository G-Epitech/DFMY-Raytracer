/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CliHandler.hpp
*/

#pragma once

#include "app/IHandler.hpp"
#include "app/App.hpp"

namespace Raytracer::Core::Cli {
    class Handler : public IHandler {
    public:
        /**
         * @brief Create a new cli handler
         * @param context Application context
         */
        explicit Handler(App::Context &context);

        /**
         * @brief Default destructor
         */
        ~Handler() override;

        /**
         * @brief Run the handler
         */
        int run() override;

    private:
        /// @brief Application arguments received from App
        App::Context &_appContext;

        /// @brief Cameras names max length
        int _camerasNamesMaxLength;

        /**
         * @brief Display the progress bar of the rendering
         * @param cameraName Name of the camera
         * @param camerasNamesMaxLength Max length of the camera names
         * @param progress Progress of the rendering
         */
        static void _displayProgress(const std::string &cameraName, int camerasNamesMaxLength, float progress);

        /**
         * @brief Display the camera label
         * @param cameraName Camera name
         * @param camerasNamesMaxLength Cameras names max length
         */
        static void _displayCameraLabel(const std::string &cameraName, int camerasNamesMaxLength);

        /**
         * @brief Get the max length of the cameras names
         * @return Cameras names max length
         */
        int _getCamerasNamesMaxLength();

        /**
         * @brief Render the image of a camera
         * @param cameraName Camera name
         * @param camera Camera object
         */
        void  _renderCameraImage(const string &cameraName, Rendering::Camera::Ptr &camera);

        /**
         * @brief Save the image of a camera
         * @param cameraName Camera name
         * @param camera Camera object
         */
        void _saveImage(const string &cameraName, Rendering::Camera::Ptr &camera) const;
    };
}
