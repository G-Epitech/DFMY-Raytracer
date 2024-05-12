/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RenderingSettings.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include "types/rendering/Camera.hpp"
#include "app/gui/widgets/RenderFrame.hpp"
#include "app/gui/GuiContext.hpp"

#define RENDERING_MAX_FLOAT 1000000
#define RENDERING_MAX_THREADS 64

namespace Raytracer::Core::Gui {
    class RenderingSettings {
    public:
        /**
         * @brief Create a new rendering settings
         * @param context The GUI context
         */
        explicit RenderingSettings(Raytracer::Core::Gui::GuiContext &context);

        /**
         * @brief Destroy the rendering settings
         */
        ~RenderingSettings();

        /**
         * @brief Initialize the rendering settings
         * @param settingsGroup Settings group
         */
        void init(tgui::Group::Ptr &settingsGroup);

        /**
         * @brief Get the rendering compute params for camera rendering
         * @return Compute params
         */
        [[nodiscard]]
        Rendering::Camera::ComputeParams getComputeParams() const;

        /**
         * @brief Set the rendering settings edition
         * @param enabled Edition status
         */
        void setRenderingSensitiveEnabled(bool enabled);

        /// @brief Render button
        tgui::Button::Ptr renderButton;
        /// @brief Cancel button
        tgui::Button::Ptr cancelButton;
        /// @brief Save button
        tgui::Button::Ptr saveButton;

    private:
        /// @brief Rendering settings layout
        tgui::Panel::Ptr _settingsPanel;
        /// @brief GUI context
        Raytracer::Core::Gui::GuiContext &_context;
        /// @brief Threads count
        tgui::SpinControl::Ptr _threadsCount;
        /// @brief Additional frames count
        tgui::SpinControl::Ptr _additionalFrames;
        /// @brief Rays per pixel count
        tgui::SpinControl::Ptr _raysPerPixel;
        /// @brief Max ray bounce count
        tgui::SpinControl::Ptr _maxRayBounce;

        /**
         * @brief Initialize the rendering settings layout
         */
        void _initInputs();

        /**
         * @brief Initialize the rendering settings buttons
         */
        void _initButtons();
    };
}
