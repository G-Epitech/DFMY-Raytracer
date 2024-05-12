/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RightPanel.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include "app/gui/GuiContext.hpp"
#include "app/gui/components/ObjectProperties.hpp"

namespace Raytracer::Core::Gui {
    class RightPanel {
    public:
        /**
         * @brief Construct a new Right Panel object
         * @param context GUI context
         */
        explicit RightPanel(GuiContext &context);

        /**
         * @brief Destroy the Right Panel object
         */
        ~RightPanel();

        /**
         * @brief Initialize the right panel
         * @param mainPanel Parent panel in which the right panel will be added
         */
        void init(tgui::Panel::Ptr &mainPanel);

    private:
        std::size_t _selectedObj;

        /// @brief GUI context
        GuiContext &_context;

        /// @brief Panel
        tgui::Panel::Ptr _panel;

        /// @brief Objects list window
        tgui::ChildWindow::Ptr _objectsListWindow;

        /// @brief Objects properties window
        tgui::ChildWindow::Ptr _objectsPropertiesWindow;

        tgui::Group::Ptr _settingsGroup;

        /// @brief Tree of objects
        tgui::TreeView::Ptr _objectTree;

        tgui::EditBox::Ptr _objName;

        ObjectProperties _objProps;

        void _initObjectTree();
        void _initObjectProperties();
    };
}
