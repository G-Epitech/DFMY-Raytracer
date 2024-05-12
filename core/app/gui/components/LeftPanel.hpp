/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RightPanel.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include "app/gui/GuiContext.hpp"
#include "CameraPanel.hpp"

namespace Raytracer::Core::Gui {
    class LeftPanel {
    public:
        /**
         * @brief Construct a new Left Panel object
         * @param context GUI context
         */
        explicit LeftPanel(GuiContext &context);

        /**
         * @brief Destroy the Right Panel object
         */
        ~LeftPanel();

        /**
         * @brief Initialize the left panel
         * @param mainPanel Parent panel in which the left panel will be added
         */
        void init(tgui::Panel::Ptr &mainPanel);

    private:
        /// @brief GUI context
        GuiContext &_context;

        /// @brief Panel
        tgui::Panel::Ptr _panel;

        /// @brief Tab container
        tgui::TabContainer::Ptr _tabContainer;

        /// @brief List of all cameras panels
        std::list<CameraPanel> _camerasPanels;

        /**
         * @brief Initialize the tab container
         */
        void _initTabContainer();
    };
}
