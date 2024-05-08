/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.cpp
*/

#include "Handler.hpp"

using namespace Raytracer::Core::Gui;

Handler::Handler(Raytracer::Core::App::Arguments &args) : _args(args), _form(_context) {
    _initGui();
}

Handler::~Handler() = default;

int Handler::run() {
    if (_form.init())
        _context.gui.mainLoop("#646464");
    return 0;
}

void Handler::_initGui() {
    _window.create({1280, 800}, "Raytracer");
    _window.setFramerateLimit(60);
    if (_icon.loadFromFile("resources/assets/icon.png")) {
        _window.setIcon(_icon.getSize().x, _icon.getSize().y, _icon.getPixelsPtr());
    }

    tgui::Theme::setDefault("resources/theme.txt");
    _context.gui.setWindow(_window);
}
