/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RightPanel.cpp
*/

#include "RightPanel.hpp"

using namespace Raytracer::Core::Gui;

RightPanel::RightPanel(GuiContext &context) :
    _selectedObj(0),
    _context(context),
    _objProps(_context.app.scene->objects[_selectedObj])
{}

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

    _objectsPropertiesWindow = tgui::ChildWindow::create();
    _objectsPropertiesWindow->setTitle("Properties");
    _objectsPropertiesWindow->setSize("100%", "60% - 10");
    _objectsPropertiesWindow->setPosition(0, "ObjectsList.height + 10");
    _objectsPropertiesWindow->setTextSize(13);
    _objectsPropertiesWindow->setPositionLocked();
    _objectsPropertiesWindow->setTitleAlignment(tgui::HorizontalAlignment::Center);
    _objectsPropertiesWindow->setTitleButtons(tgui::ChildWindow::TitleButton::None);
    _initObjectProperties();
    _panel->add(_objectsPropertiesWindow);

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

void RightPanel::_initObjectProperties()
{
    _settingsGroup = tgui::Group::create({"100%", "100%"});
    _settingsGroup->setPosition(0, 0);
    _settingsGroup->getRenderer()->setPadding(0);
    _objProps.init(_settingsGroup);
    _objectsPropertiesWindow->add(_settingsGroup);
}
