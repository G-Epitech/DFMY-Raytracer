/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MainPanel.cpp
*/

#include "MainPanel.hpp"
#include "app/gui/GuiContext.hpp"

using namespace Raytracer::Core::Gui;

MainPanel::MainPanel(GuiContext &context):
    _context(context),
    _rightPanel(context),
    _leftPanel(context)
    {}

void MainPanel::init() {
    _panel = tgui::Panel::create();

    _panel->setSize("100%", "&.height - 40");

    _panel->setPosition(0, 20);
    _panel->setTextSize(13);
    _panel->getRenderer()->setBackgroundColor(sf::Color::Transparent);

    _rightPanel.init(_panel);
    _leftPanel.init(_panel);

    _context.gui.add(_panel);
}

MainPanel::~MainPanel() = default;
