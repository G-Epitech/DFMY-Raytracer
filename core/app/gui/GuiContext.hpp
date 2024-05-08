/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** GUIContext.hpp
*/

#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Raytracer::Core::Gui {
    struct GuiContext {
        /// @brief TGUI GUI
        tgui::Gui gui;
    };
}
