/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"

using namespace Raytracer::Core::Gui;

MenuBar::MenuBar(GuiContext &context): _context(context) {}

void MenuBar::init() {
    _menuBar = tgui::MenuBar::create();

    _menuBar->setSize("100%", 20);
    _menuBar->setMinimumSubMenuWidth(125);
    _menuBar->setTextSize(13);

    _menuBar->addMenu("File");
    _menuBar->addMenuItem({ "File", "Open" });
    _menuBar->addMenuItem({ "File", "Save image as", "PPM" });
    _menuBar->addMenuItem({ "File", "Save image as", "PNG" });
    _menuBar->addMenuItem({ "File", "Save image as", "JPG" });
    _menuBar->addMenuItem({ "File", "Save image as", "BMP" });
    _menuBar->addMenuItem({ "File", "Quit" });

    _menuBar->addMenu("Scene");
    _menuBar->addMenuItem({ "Scene", "Cameras", "Add" });
    _menuBar->addMenuItem({ "Scene", "Objects", "Add" });
    _menuBar->addMenuItem({ "Scene", "Materials", "Add" });
    _menuBar->addMenuItem({ "Scene", "Lights", "Add" });

    _menuBar->addMenu("Help");
    _menuBar->addMenuItem({ "Help", "About" });

    _context.gui.add(_menuBar);
}

MenuBar::~MenuBar() = default;
