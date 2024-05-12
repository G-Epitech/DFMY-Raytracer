/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MainPanel.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include "app/gui/GuiContext.hpp"
#include "RightPanel.hpp"
#include "LeftPanel.hpp"

namespace Raytracer::Core::Gui {
    class MainPanel {
    public:
        /**
         * @brief Create a new main panel
         * @param context GUI context
         */
        explicit MainPanel(GuiContext &context);

        /**
         * @brief Destroy the main panel
         */
        ~MainPanel();

        /**
         * @brief Load the main panel components
         */
        void init();

    private:
        /// @brief GUI context
        GuiContext &_context;

        /// @brief TGUI panel
        tgui::Panel::Ptr _panel;

        /// @brief Right panel
        RightPanel _rightPanel;

        /// @brief Left panel
        LeftPanel _leftPanel;
    };
}
