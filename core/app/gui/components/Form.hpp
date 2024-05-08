/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Form.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "app/gui/GuiContext.hpp"
#include "MenuBar.hpp"
#include "StatusBar.hpp"
#include "MainPanel.hpp"

namespace Raytracer::Core::Gui {
    class Form {
    public:
        /**
         * @brief Create a new form
         * @param context The GUI context
         */
        explicit Form(GuiContext &context);

        /**
         * @brief Destroy the form
         */
        ~Form();

        /**
         * @brief Load the form components
         */
        bool init();

    private:
        /// @brief TGUI GUI
        GuiContext &_context;

        /// @brief Menu bar
        MenuBar _menuBar;

        /// @brief Status bar
        StatusBar _statusBar;

        /// @brief Main panel
        MainPanel _mainPanel;
    };
}