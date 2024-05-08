/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** StatusBar.cpp
*/

#include <TGUI/Widgets/Label.hpp>
#include "StatusBar.hpp"

using namespace Raytracer::Core::Gui;

StatusBar::StatusBar(GuiContext &context) : _context(context) {}

void StatusBar::init() {
    _layout = tgui::HorizontalLayout::create();

    _layout->setSize("100%", 20);
    _layout->setPosition(0, "&.height - height");
    _layout->setTextSize(13);

    _left = tgui::HorizontalLayout::create();
    _left->setSize("50%", "100%");
    _layout->add(_left);

    _right = tgui::HorizontalLayout::create();
    _right->setSize("50%", "100%");
    _layout->add(_right);

    _label = tgui::Label::create();
    _label->setText("Ready");
    _label->setTextSize(13);
    _label->setPosition("(parent.width - width) / 2", "(parent.height - height) / 2");
    _left->add(_label);

    _context.gui.add(_layout);
}

StatusBar::~StatusBar() = default;
