/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** StatusBar.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>

namespace Raytracer::Core::Gui {
    class GuiContext;

    class StatusBar {
    public:
        /// @brief Shared pointer of StatusBar
        typedef std::shared_ptr<StatusBar> Ptr;

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
         * @brief Create a new status bar
         * @param context GUI context
         * @return Created status bar
         */
        static StatusBar::Ptr create(GuiContext &context);

        /**
         * @brief Initialize the status bar
         */
        void init();

        /// @brief Current operation status label
        tgui::Label::Ptr statusLabel;

        /// @brief Progress bar
        tgui::ProgressBar::Ptr progressBar;

    private:
        /// @brief GUI context
        GuiContext &_context;

        /// @brief Layout
        tgui::HorizontalLayout::Ptr _layout;

        /// @brief Left part of bar
        tgui::Panel::Ptr _left;

        /// @brief Right part of bar
        tgui::Panel::Ptr _right;

    };
}
