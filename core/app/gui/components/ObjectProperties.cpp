/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ObjectProperties
*/

#include "ObjectProperties.hpp"

using namespace Raytracer::Core::Gui;

ObjectProperties::ObjectProperties(Raytracer::Common::IObject::Ptr obj)
    :   _obj(std::move(obj))
{
}

void ObjectProperties::init(tgui::Group::Ptr &settingsGroup)
{
    _propertiesPanel = tgui::ScrollablePanel::create();
    _propertiesPanel->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Automatic);
    _propertiesPanel->setSize("100%", "100%");
    _propertiesPanel->getRenderer()->setPadding(10);

    _initPropertiesName();
    _initPropertiesPosition();
    _initPropertiesDirection();
    settingsGroup->add(_propertiesPanel);
}

void ObjectProperties::changeObj(Raytracer::Common::IObject::Ptr obj)
{
    _obj = std::move(obj);
    _objName->setText(_obj->getName());
    _objPositionX->setValue(_obj->getPosition().x);
    _objPositionY->setValue(_obj->getPosition().y);
    _objPositionZ->setValue(_obj->getPosition().z);
    _objDirectionX->setValue(_obj->getRotation().x);
    _objDirectionY->setValue(_obj->getRotation().y);
    _objDirectionZ->setValue(_obj->getRotation().z);
}

void ObjectProperties::_initPropertiesName()
{
    auto label = tgui::Label::create("Name:");

    label->setWidth(60);
    label->setPosition(0, "10 + (20 - height) / 2");
    _objName = tgui::Label::create();
    _objName->setPosition(60, "10 + (20 - height) / 2");
    _objName->setPosition(100, "10 + (20 - height) / 2");
    _objName->setText(_obj->getName());
    _propertiesPanel->add(label);
    _propertiesPanel->add(_objName);
}

void ObjectProperties::_initPropertiesPosition()
{
    tgui::Layout2d inputSize = { "80%", 20 };
    auto labelPos = tgui::Label::create("Position");
    auto labelX = tgui::Label::create("x:");
    auto labelY = tgui::Label::create("y:");
    auto labelZ = tgui::Label::create("z:");

    labelPos->setWidth(100);
    labelPos->setPosition(0, "50 + (20 - height) / 2");
    labelPos->setWidgetName("labelPos");
    _propertiesPanel->add(labelPos);

    labelX->setWidth(20);
    labelX->setPosition(0, "labelPos.y + (30 + (20 - height) / 2)");
    labelX->setWidgetName("labelXPos");
    _propertiesPanel->add(labelX);

    _objPositionX = tgui::SpinControl::create(
        -1000, 1000, _obj->getPosition().x,
        2, 0.1f
    );
    _objPositionX->setSize(inputSize);
    _objPositionX->setPosition("labelXPos.right + 10", "labelXPos.y - (20 - height) / 2 - 5");
    _objPositionX->setWidgetName("objPositionX");
    _objPositionX->onValueChange([this](float value) {
        _obj->getPosition().x = value;
    });
    _propertiesPanel->add(_objPositionX);

    labelY->setWidth(20);
    labelY->setPosition(0, "labelXPos.y + 35 + (20 - height) / 2");
    labelY->setWidgetName("labelYPos");
    _propertiesPanel->add(labelY);

    _objPositionY = tgui::SpinControl::create(
        -1000, 1000, _obj->getPosition().y,
        2, 0.1f
    );
    _objPositionY->setSize(inputSize);
    _objPositionY->setPosition("labelYPos.right + 10", "labelYPos.y - (20 - height) / 2 - 5");
    _objPositionY->setWidgetName("objPositionY");
    _objPositionY->onValueChange([this](float value) {
        _obj->getPosition().y = value;
    });
    _propertiesPanel->add(_objPositionY);

    labelZ->setWidth(20);
    labelZ->setPosition(0, "labelYPos.y + 35 + (20 - height) / 2");
    labelZ->setWidgetName("labelZPos");
    _propertiesPanel->add(labelZ);

    _objPositionZ = tgui::SpinControl::create(
        -1000, 1000, _obj->getPosition().z,
        2, 0.1f
    );
    _objPositionZ->setSize(inputSize);
    _objPositionZ->setPosition("labelZPos.right + 10", "labelZPos.y - (20 - height) / 2 - 5");
    _objPositionZ->setWidgetName("objPositionZ");
    _objPositionZ->onValueChange([this](float value) {
        _obj->getPosition().z = value;
    });
    _propertiesPanel->add(_objPositionZ);
}

void ObjectProperties::_initPropertiesDirection()
{
    tgui::Layout2d inputSize = { "80%", 20 };
    auto labelDirection = tgui::Label::create("Rotation");
    auto labelX = tgui::Label::create("x:");
    auto labelY = tgui::Label::create("y:");
    auto labelZ = tgui::Label::create("z:");

    labelDirection->setWidth(100);
    labelDirection->setPosition(0, "200 + (20 - height) / 2");
    labelDirection->setWidgetName("labelDirection");
    _propertiesPanel->add(labelDirection);

    labelX->setWidth(20);
    labelX->setPosition(0, "labelDirection.y + 35 + (20 - height) / 2");
    labelX->setWidgetName("labelXDir");
    _propertiesPanel->add(labelX);

    _objDirectionX = tgui::SpinControl::create(
        -1000, 1000, _obj->getRotation().x,
        2, 0.1f
    );
    _objDirectionX->setSize(inputSize);
    _objDirectionX->setPosition("labelXDir.right + 10", "labelXDir.y - (20 - height) / 2");
    _objDirectionX->setWidgetName("objDirectionX");
    _objDirectionX->onValueChange([this](float value) {
        _obj->getRotation().x = value;
    });
    _propertiesPanel->add(_objDirectionX);

    labelY->setWidth(20);
    labelY->setPosition(0, "labelXDir.y + 35 + (20 - height) / 2");
    labelY->setWidgetName("labelYDir");
    _propertiesPanel->add(labelY);

    _objDirectionY = tgui::SpinControl::create(
        -1000, 1000, _obj->getRotation().y,
        2, 0.1f
    );
    _objDirectionY->setSize(inputSize);
    _objDirectionY->setPosition("labelYDir.right + 10", "labelYDir.y - (20 - height) / 2");
    _objDirectionY->setWidgetName("objDirectionY");
    _objDirectionY->onValueChange([this](float value) {
        _obj->getRotation().y = value;
    });
    _propertiesPanel->add(_objDirectionY);

    labelZ->setWidth(20);
    labelZ->setPosition(0, "labelYDir.y + 35 + (20 - height) / 2");
    labelZ->setWidgetName("labelZDir");
    _propertiesPanel->add(labelZ);

    _objDirectionZ = tgui::SpinControl::create(
        -1000, 1000, _obj->getRotation().z,
        2, 0.1f
    );
    _objDirectionZ->setSize(inputSize);
    _objDirectionZ->setPosition("labelZDir.right + 10", "labelZDir.y - (20 - height) / 2");
    _objDirectionZ->setWidgetName("objDirectionZ");
    _objDirectionZ->onValueChange([this](float value) {
        _obj->getRotation().z = value;
    });
    _propertiesPanel->add(_objDirectionZ);
}
