/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RightPanel.cpp
*/

#include "RightPanel.hpp"

using namespace Raytracer::Core::Gui;

RightPanel::RightPanel(GuiContext &context) : _context(context) {}

RightPanel::~RightPanel() = default;

void RightPanel::init(tgui::Panel::Ptr &mainPanel) {
    _panel = tgui::Panel::create();
    _panel->setSize("20%", "100%");
    _panel->setPosition("&.width - width", 0);
    _panel->getRenderer()->setPadding(10);
    _panel->getRenderer()->setBorders(0);

    _objectsListWindow = tgui::ChildWindow::create();
    _objectsListWindow->setTitle("Objects");
    _objectsListWindow->setWidgetName("ObjectsList");
    _objectsListWindow->setSize("100%", "40%");
    _objectsListWindow->setPosition(0, 0);
    _objectsListWindow->setTextSize(13);
    _objectsListWindow->setPositionLocked();
    _objectsListWindow->setTitleAlignment(tgui::HorizontalAlignment::Center);
    _objectsListWindow->setTitleButtons(tgui::ChildWindow::TitleButton::None);
    _initObjectTree();
    _panel->add(_objectsListWindow);

    _objectsListWindow = tgui::ChildWindow::create();
    _objectsListWindow->setTitle("Properties");
    _objectsListWindow->setSize("100%", "60% - 10");
    _objectsListWindow->setPosition(0, "ObjectsList.height + 10");
    _objectsListWindow->setTextSize(13);
    _objectsListWindow->setPositionLocked();
    _objectsListWindow->setTitleAlignment(tgui::HorizontalAlignment::Center);
    _objectsListWindow->setTitleButtons(tgui::ChildWindow::TitleButton::None);
    _panel->add(_objectsListWindow);

    mainPanel->add(_panel);
}

void RightPanel::_initObjectTree()
{
    _objectTree = tgui::TreeView::create();
    _objectTree->setSize("100%", "100%");
    for (auto &obj : _context.app.scene->objects) {
        _objectTree->addItem({obj->getType(), obj->getName()}, true);
    }
    _objectsListWindow->add(_objectTree);
}
