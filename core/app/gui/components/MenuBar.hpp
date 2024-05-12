/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MenuBar.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include "app/gui/GuiContext.hpp"

namespace Raytracer::Core::Gui {
    class MenuBar {
    public:
        /**
         * @brief Create a new menu bar
         */
        explicit MenuBar(GuiContext &context);

        /**
         * @brief Destroy the menu bar
         */
        ~MenuBar();

        /**
         * @brief Initialize the menu bar
         */
        void init();

    private:
        /// @brief TGUI GUI
        GuiContext &_context;

        /// @brief TGUI Menu bar
        tgui::MenuBar::Ptr _menuBar;

        /// @brief About message box
        tgui::MessageBox::Ptr _aboutBox;

        /**
         * @brief Initialize the menu bar events
         */
        void _initEvents();

        /**
         * @brief Initialize the about box
         */
        void _openAboutBox();
    };
}
