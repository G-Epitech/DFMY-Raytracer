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
    label->setPosition(0, "10 + (20 - height) / 2");
    _objName = tgui::EditBox::create();
    _objName->setSize("70%", 25);
    _objName->setPosition("parent.right - width - 23", 10);
    _objName->setText(_obj->getName());
    _propertiesPanel->add(label);
    _propertiesPanel->add(_objName);
}

void ObjectProperties::_initPropertiesPosition()
{
    tgui::Layout2d inputSize = { "(parent.w - 200) / 3", 20};
    auto labelPos = tgui::Label::create("Position");
    auto labelX = tgui::Label::create("x:");
    auto labelY = tgui::Label::create("y:");
    auto labelZ = tgui::Label::create("z:");

    labelPos->setWidth(100);
    labelPos->setPosition(0, "50 + (20 - height) / 2");
    labelPos->setWidgetName("labelPos");
    _propertiesPanel->add(labelPos);

    labelX->setWidth(20);
    labelX->setPosition(0, "labelPos.y + 35 + (20 - height) / 2");
    labelX->setWidgetName("labelX");
    _propertiesPanel->add(labelX);

    _objPositionX = tgui::SpinControl::create(
        -1000, 1000, 30,
        2, 0.1f
    );
    _objPositionX->setSize(inputSize);
    _objPositionX->setPosition("labelX.right + 150", "labelX.y - (20 - height) / 2");
    _objPositionX->setWidgetName("objPositionX");
    _propertiesPanel->add(_objPositionX);

    labelY->setWidth(20);
    labelY->setPosition(0, "labelX.y + 35 + (20 - height) / 2");
    labelY->setWidgetName("labelY");
    _propertiesPanel->add(labelY);

    _objPositionY = tgui::SpinControl::create(
        -1000, 1000, 30,
        2, 0.1f
    );
    _objPositionY->setSize(inputSize);
    _objPositionY->setPosition("labelY.right + 150", "labelY.y - (20 - height) / 2");
    _objPositionY->setWidgetName("objPositionY");
    _propertiesPanel->add(_objPositionY);

    labelZ->setWidth(20);
    labelZ->setPosition(0, "labelY.y + 35 + (20 - height) / 2");
    labelZ->setWidgetName("labelZ");
    _propertiesPanel->add(labelZ);

    _objPositionZ = tgui::SpinControl::create(
        -1000, 1000, 30,
        2, 0.1f
    );
    _objPositionZ->setSize(inputSize);
    _objPositionZ->setPosition("labelZ.right + 150", "labelZ.y - (20 - height) / 2");
    _objPositionZ->setWidgetName("objPositionZ");
    _propertiesPanel->add(_objPositionZ);
}
