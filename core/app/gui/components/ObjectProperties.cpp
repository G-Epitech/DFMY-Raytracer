/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ObjectProperties
*/

#include "ObjectProperties.hpp"

using namespace Raytracer::Core::Gui;

ObjectProperties::ObjectProperties(Raytracer::Common::IObject::Ptr &obj)
    :   _obj(obj)
{
}

void ObjectProperties::init(tgui::Group::Ptr &settingsGroup)
{
    _propertiesPanel = tgui::Panel::create();
    _propertiesPanel->setSize("100%", "100%");
    _propertiesPanel->getRenderer()->setPadding(10);

    _initPropertiesName();
    _initPropertiesPosition();
    settingsGroup->add(_propertiesPanel);
}

void ObjectProperties::_initPropertiesName()
{
    auto label = tgui::Label::create("Name:");

    label->setWidth(90);
    label->setPosition(0, "35 + (25 - height) / 2");
    _objName = tgui::EditBox::create();
    _objName->setSize("70%", 25);
    _objName->setPosition("parent.right - width - 23", 35);
    _propertiesPanel->add(label);
    _propertiesPanel->add(_objName);
}

void ObjectProperties::_initPropertiesPosition()
{
    tgui::Layout2d inputSize = { "(parent.w - 243) / 3", 25 };
    auto labelX = tgui::Label::create("Position:       x:");
    auto labelY = tgui::Label::create("y:");
    auto labelZ = tgui::Label::create("z:");

    labelX->setWidth(100);
    labelX->setPosition(0, "75 + (25 - height) / 2");
    labelX->setWidgetName("cameraPositionXLabel");
    _propertiesPanel->add(labelX);
}
