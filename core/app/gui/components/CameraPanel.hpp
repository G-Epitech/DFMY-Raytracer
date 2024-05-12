/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CameraPanel.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include "types/rendering/Camera.hpp"
#include "app/gui/GuiContext.hpp"
#include "app/gui/widgets/RenderFrame.hpp"
#include "CameraProperties.hpp"
#include "RenderingSettings.hpp"

namespace Raytracer::Core::Gui {
    class CameraPanel {
    public:
        /**
         * @brief Construct a new CameraPanel object
         * @param name Name of the camera
         * @param camera Camera object reference
         */
        explicit CameraPanel(
            Rendering::Camera::Ptr &camera,
            Core::Gui::GuiContext &context,
            tgui::TabContainer::Ptr &tabContainer
        );

        /**
         * @brief Destroy the CameraPanel object
         */
        ~CameraPanel();

        /**
         * @brief On tab selected
         */
        void onTabSelected();

        /**
         * @brief On tab unselected
         */
        void onTabUnselected();

    private:
        /// @brief Gui context
        Core::Gui::GuiContext &_context;
        /// @brief Panel object
        tgui::Panel::Ptr _panel;
        /// @brief Tab container
        tgui::TabContainer::Ptr _tabContainer;
        /// @brief Render frame
        Raytracer::Core::Gui::RenderFrame::Ptr _frame;
        /// @brief Camera object
        Rendering::Camera::Ptr _camera;
        /// @brief Rendering thread
        std::thread _renderingThread;
        /// @brief Render container
        tgui::Panel::Ptr _renderPanel;
        /// @brief Settings panel
        tgui::Group::Ptr _settingsGroup;
        /// @brief Camera properties panel
        Raytracer::Core::Gui::CameraProperties _propertiesPanel;
        /// @brief Rendering settings panel
        Raytracer::Core::Gui::RenderingSettings _renderingSettingsPanel;
        /// @brief Auto paused flag
        bool _autoPaused = false;

        /**
         * @brief Initialize the render panel
         */
        void _initRenderPanel();

        /**
         * @brief Initialize the settings panel
         */
        void _initSettingsGroup();

        /**
         * @brief Render the camera panel
         */
        void _render();

        /**
         * @brief On render button clicked
         */
        void _onRenderButtonClicked();

        /**
         * @brief On cancel button clicked
         */
        void _onCancelButtonClicked();

        /**
         * @brief Update the status bar
         */
        void _updateStatusBar();
    };
}