/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** LeftPanel.cpp
*/

#include <iostream>
#include "LeftPanel.hpp"

using namespace Raytracer::Core::Gui;

LeftPanel::LeftPanel(GuiContext &context) : _context(context) {}

LeftPanel::~LeftPanel() = default;

void LeftPanel::init(tgui::Panel::Ptr &mainPanel) {
    _panel = tgui::Panel::create();
    _panel->setSize("80%", "100%");
    _panel->setPosition(0, 0);
    _panel->getRenderer()->setPadding(10);

    _initTabContainer();

    mainPanel->add(_panel);
}

void LeftPanel::_initTabContainer() {
    _tabContainer = tgui::TabContainer::create();

    _tabContainer->setTabsHeight(25);
    _tabContainer->setTabFixedSize(100);
    _tabContainer->setSize("100%", "100%");
    _tabContainer->setTabAlignment(tgui::TabContainer::TabAlign::Top);

    for (int i = 0; i < 3; ++i) {
        auto name = "Camera " + std::to_string(i + 1);
        auto tab = _tabContainer->addTab(name);
        _initTabPanel(tab, "Camera " + std::to_string(i + 1));
    }
    _tabContainer->onSelectionChange([](int index){
        std::cerr << "The tab and panel with index " << index << " is now selected\n";
    });
    _panel->add(_tabContainer);
}

void LeftPanel::_initTabPanel(tgui::Panel::Ptr &tabPanel, const std::string &tabName) {
    auto button = tgui::Button::create();
    button->setText("Button inside " + tabName);
    button->onClick([]{
        std::cerr << "Button inside tab clicked\n";
    });
    tabPanel->add(button);
}
