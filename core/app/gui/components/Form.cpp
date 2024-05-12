/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Form.cpp
*/

#include "Form.hpp"
#include "app/gui/GuiContext.hpp"

using namespace Raytracer::Core::Gui;

Form::Form(GuiContext &context):
    _context(context),
    _menuBar(context),
    _statusBar(nullptr),
    _mainPanel(context)
    {}

Form::~Form() = default;

bool Form::init() {
    _statusBar = StatusBar::create(_context);
    _statusBar->init();
    _context.statusBar = _statusBar;
    _menuBar.init();
    _mainPanel.init();
    return true;
}
