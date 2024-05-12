/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CameraProperties.hpp
*/

#pragma once

#include <cfloat>
#include <TGUI/TGUI.hpp>
#include "types/rendering/Camera.hpp"

#define CAMERA_COORD_LIMIT 1000000

namespace Raytracer::Core::Gui {
    class CameraProperties {
    public:
        /**
         * @brief Create a new camera properties panel
         */
        explicit CameraProperties(Raytracer::Core::Rendering::Camera::Ptr camera);

        /**
         * @brief Destroy the camera properties panel
         */
        ~CameraProperties();

        /**
         * @brief Initialize the camera properties panel
         * @param settingsGroup The settings group
         */
        void init(tgui::Group::Ptr &settingsGroup);

        /**
         * @brief Set the camera properties panel edition
         * @param enabled The edition status
         */
        void setEnabled(bool enabled);

    private:
        /// @brief Camera object
        Raytracer::Core::Rendering::Camera::Ptr _camera;
        /// @brief Camera properties layout
        tgui::Panel::Ptr _propertiesPanel;
        /// @brief Camera name
        tgui::EditBox::Ptr _cameraName;
        /// @brief Camera position X
        tgui::SpinControl::Ptr _cameraPositionX;
        /// @brief Camera position Y
        tgui::SpinControl::Ptr _cameraPositionY;
        /// @brief Camera position Z
        tgui::SpinControl::Ptr _cameraPositionZ;
        /// @brief Camera direction X
        tgui::SpinControl::Ptr _cameraDirectionX;
        /// @brief Camera direction Y
        tgui::SpinControl::Ptr _cameraDirectionY;
        /// @brief Camera direction Z
        tgui::SpinControl::Ptr _cameraDirectionZ;
        /// @brief Camera FOV
        tgui::SpinControl::Ptr _cameraFOV;
        /// @brief Screen width
        tgui::SpinControl::Ptr _screenWidth;
        /// @brief Screen height
        tgui::SpinControl::Ptr _screenHeight;
        /// @brief Apply button
        tgui::Button::Ptr _applyButton;
        /// @brief Cancel button
        tgui::Button::Ptr _resetButton;

        /**
         * @brief Initialize the camera name
         */
        void _initCameraName();

        /**
         * @brief Initialize the camera position
         */
        void _initCameraPosition();

        /**
         * @brief Initialize the camera position
         */
        void _initCameraDirection();

        /**
         * @brief Initialize the camera FOV
         */
        void _initCameraFOV();

        /**
         * @brief Initialize the screen
         */
        void _initScreen();

        /**
         * @brief Initialize the on change events
         */
        void _initOnChangeEvents();

        /**
         * @brief On apply button click
         */
        void _onApply();

        /**
         * @brief On cancel button click
         */
        void _onReset();

        /**
         * @brief Check if the configuration has changed
         * @return Configuration changed status
         */
        [[nodiscard]]
        bool _configurationChanged() const;
    };
}
