/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** LeftPanel.cpp
*/

#include "LeftPanel.hpp"

using namespace Raytracer::Core::Gui;

LeftPanel::LeftPanel(GuiContext &context) : _context(context) {}

LeftPanel::~LeftPanel() = default;

void LeftPanel::init(tgui::Panel::Ptr &mainPanel) {
    _panel = tgui::Panel::create();
    _panel->setSize("80%", "100%");
    _panel->getRenderer()->setBorders(0);
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
    _tabContainer->onSelectionChanging([this] {
        auto tabIndex = _tabContainer->getSelectedIndex();
        size_t i = 0;

        for (auto &panel : _camerasPanels) {
            if (i == tabIndex)
                panel.onTabSelected();
            else
                panel.onTabUnselected();
            i += 1;
        }
    });

    for (auto &[_, camera] : _context.app.scene->cameras) {
        _camerasPanels.emplace_back(camera, _context, _tabContainer);
    }
    _panel->add(_tabContainer);
}

