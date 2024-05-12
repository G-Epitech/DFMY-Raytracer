/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"
#include "config/Config.hpp"

using namespace Raytracer::Core::Gui;

MenuBar::MenuBar(GuiContext &context): _context(context) {}

void MenuBar::init() {
    _menuBar = tgui::MenuBar::create();

    _menuBar->setSize("100%", 20);
    _menuBar->setMinimumSubMenuWidth(125);
    _menuBar->setTextSize(13);

    _menuBar->addMenu("File");
    _menuBar->addMenuItem({ "File", "Open" });
    _menuBar->addMenuItem({ "File", "Quit" });

    _menuBar->addMenu("Help");
    _menuBar->addMenuItem({ "Help", "About" });

    _initEvents();
    _context.gui.add(_menuBar);
}

void MenuBar::_initEvents() {
    _menuBar->connectMenuItem({ "File", "Quit" }, [this]() { _context.gui.getWindow()->close(); });
    _menuBar->connectMenuItem({ "File", "Open" }, [this]() { _openFileExplorer(); });
    _menuBar->connectMenuItem({ "Help", "About" }, [this]() { _openAboutBox(); });
}

void MenuBar::_openAboutBox() {
    std::stringstream aboutText;

    aboutText << "Raytracer\n\n";
    aboutText << "Authors:\n";
    aboutText << "\tDragos Suceveanu, Flavien Chenu,\n";
    aboutText << "\tMatheo Coquet & Yann Masson\n\n";
    aboutText << "Version: 1.0.0\n";
    aboutText << "Build date: " << __DATE__ << " " << __TIME__ << "\n\n";
    aboutText << "All rights reserved.";

    _aboutBox = tgui::MessageBox::create("About", aboutText.str());
    _aboutBox->addButton("OK");
    _aboutBox->onButtonPress.connect([this]() {
        _aboutBox->setVisible(false);
    });
    _aboutBox->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
    _context.gui.add(_aboutBox);
}

void MenuBar::_openFileExplorer()
{
    auto fileDialog = tgui::FileDialog::create();
    fileDialog->setTitle("Open file");
    fileDialog->setFileMustExist(true);
    fileDialog->setFileTypeFilters({{"Raytracer Config", {"*.cfg"}}});
    fileDialog->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
    fileDialog->onFileSelect([this](const tgui::String &selectedFile) {
        try {
            auto config = Config::loadFromFile(selectedFile.toStdString(), _context.app.pluginsManager);
            auto scene = config.toScene();

            _context.app.scene = std::move(scene);
        } catch (const std::exception &e) {
            auto messageBox = tgui::MessageBox::create("Error", e.what(), {"OK"});

            messageBox->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
            messageBox->onButtonPress([this, messageBox]() {
                _context.gui.remove(messageBox);
            });
            _context.gui.add(messageBox);
        }
    });
    _context.gui.add(fileDialog);
}

MenuBar::~MenuBar() = default;
