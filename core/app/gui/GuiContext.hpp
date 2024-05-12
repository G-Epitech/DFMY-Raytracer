/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** GUIContext.hpp
*/

#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>

#include "../App.hpp"
#include "TGui.hpp"
#include "app/gui/components/StatusBar.hpp"

namespace Raytracer::Core::Gui {
    struct GuiContext {
        /// @brief TGUI GUI
        Raytracer::Core::Gui::TGui gui;
        /// @brief Status bar
        Raytracer::Core::Gui::StatusBar::Ptr statusBar;
        /// @brief App context
        Raytracer::Core::App::Context &app;
    };
}
