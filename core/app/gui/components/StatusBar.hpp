/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** StatusBar.hpp
*/

#pragma once

#include <TGUI/Widgets/HorizontalLayout.hpp>
#include "app/gui/GuiContext.hpp"

namespace Raytracer::Core::Gui {
    class StatusBar {
    public:
        /**
         * @brief Construct a new StatusBar object
         * @param context GUI context
         */
        explicit StatusBar(GuiContext &context);

        /**
         * @brief Destroy the StatusBar object
         */
        ~StatusBar();

        /**
         * @brief Initialize the status bar
         */
        void init();

    private:
        /// @brief GUI context
        GuiContext &_context;

        /// @brief Layout
        tgui::HorizontalLayout::Ptr _layout;

        /// @brief Left part of bar
        tgui::HorizontalLayout::Ptr _left;

        /// @brief Right part of bar
        tgui::HorizontalLayout::Ptr _right;

        /// @brief Current operation status label
        tgui::Label::Ptr _label;
    };
}
