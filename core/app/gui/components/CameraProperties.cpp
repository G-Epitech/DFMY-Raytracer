/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CameraProperties.cpp
*/

#include "CameraProperties.hpp"

#include <utility>

using namespace Raytracer::Core::Gui;

CameraProperties::~CameraProperties() = default;

CameraProperties::CameraProperties(Raytracer::Core::Rendering::Camera::Ptr camera):
    _camera(std::move(camera)) {}

void CameraProperties::init(tgui::Group::Ptr &settingsGroup) {
    auto label = tgui::Label::create("Camera properties");
    label->getRenderer()->setTextSize(15);
    label->getRenderer()->setTextStyle("medium");

    _propertiesPanel = tgui::Panel::create();
    _propertiesPanel->setSize("60%", "100%");
    _propertiesPanel->getRenderer()->setPadding(10);
    _propertiesPanel->add(label);

    _initCameraName();
    _initCameraPosition();
    _initCameraDirection();
    _initCameraFOV();
    _initScreen();
    _initOnChangeEvents();

    settingsGroup->add(_propertiesPanel);
}

void CameraProperties::_initCameraName() {
    auto label = tgui::Label::create("Name:");
    label->setWidth(90);
    label->setPosition(0, "35 + (25 - height) / 2");

    _cameraName = tgui::EditBox::create();
    _cameraName->setSize("100% - 100", 25);
    _cameraName->setPosition("parent.right - width - 23", 35);
    _cameraName->setText(_camera->name);

    _propertiesPanel->add(label);
    _propertiesPanel->add(_cameraName);
}

void CameraProperties::_initCameraPosition() {
    tgui::Layout2d inputSize = { "(parent.w - 243) / 3", 25 };
    auto labelX = tgui::Label::create("Position:       x:");
    auto labelY = tgui::Label::create("y:");
    auto labelZ = tgui::Label::create("z:");

    labelX->setWidth(100);
    labelX->setPosition(0, "75 + (25 - height) / 2");
    labelX->setWidgetName("cameraPositionXLabel");
    _propertiesPanel->add(labelX);

    _cameraPositionX = tgui::SpinControl::create(
        -1000, 1000, _camera->position.x,
        2, 0.1f
    );
    _cameraPositionX->setPosition("cameraPositionXLabel.right", 75);
    _cameraPositionX->setSize(inputSize);
    _cameraPositionX->setWidgetName("cameraPositionX");
    _propertiesPanel->add(_cameraPositionX);

    labelY->setWidth(20);
    labelY->setPosition("cameraPositionX.right + 30", "75 + (25 - height) / 2");
    labelY->setWidgetName("cameraPositionYLabel");
    _propertiesPanel->add(labelY);

    _cameraPositionY = tgui::SpinControl::create(
        -CAMERA_COORD_LIMIT, CAMERA_COORD_LIMIT, _camera->position.y,
        2, 0.1f
    );
    _cameraPositionY->setPosition("cameraPositionYLabel.right + 10", 75);
    _cameraPositionY->setSize(inputSize);
    _cameraPositionY->setWidgetName("cameraPositionY");
    _propertiesPanel->add(_cameraPositionY);

    labelZ->setWidth(20);
    labelZ->setPosition("cameraPositionY.right + 30", "75 + (25 - height) / 2");
    labelZ->setWidgetName("cameraPositionZLabel");
    _propertiesPanel->add(labelZ);

    _cameraPositionZ = tgui::SpinControl::create(
        -CAMERA_COORD_LIMIT, CAMERA_COORD_LIMIT, _camera->position.z,
        2, 0.1f
    );
    _cameraPositionZ->setPosition("cameraPositionZLabel.right + 10", 75);
    _cameraPositionZ->setSize(inputSize);
    _propertiesPanel->add(_cameraPositionZ);
}

void CameraProperties::_initCameraDirection() {
    tgui::Layout2d inputSize = { "(parent.w - 243) / 3", 25 };
    auto labelX = tgui::Label::create("Direction:     x:");
    auto labelY = tgui::Label::create("y:");
    auto labelZ = tgui::Label::create("z:");

    labelX->setWidth(100);
    labelX->setPosition(0, "115 + (25 - height) / 2");
    labelX->setWidgetName("cameraDirectionXLabel");
    _propertiesPanel->add(labelX);

    _cameraDirectionX = tgui::SpinControl::create(
        -CAMERA_COORD_LIMIT, CAMERA_COORD_LIMIT, _camera->direction.x,
        2, 0.1f
    );
    _cameraDirectionX->setPosition("cameraDirectionXLabel.right", 115);
    _cameraDirectionX->setSize(inputSize);
    _cameraDirectionX->setWidgetName("cameraDirectionX");
    _propertiesPanel->add(_cameraDirectionX);

    labelY->setWidth(20);
    labelY->setPosition("cameraDirectionX.right + 30", "115 + (25 - height) / 2");
    labelY->setWidgetName("cameraDirectionYLabel");
    _propertiesPanel->add(labelY);

    _cameraDirectionY = tgui::SpinControl::create(
        -CAMERA_COORD_LIMIT, CAMERA_COORD_LIMIT, _camera->direction.y,
        2, 0.1f
    );
    _cameraDirectionY->setPosition("cameraDirectionYLabel.right + 10", 115);
    _cameraDirectionY->setSize(inputSize);
    _cameraDirectionY->setWidgetName("cameraDirectionY");
    _propertiesPanel->add(_cameraDirectionY);


    labelZ->setWidth(20);
    labelZ->setPosition("cameraDirectionY.right + 30", "115 + (25 - height) / 2");
    labelZ->setWidgetName("cameraDirectionZLabel");
    _propertiesPanel->add(labelZ);

    _cameraDirectionZ = tgui::SpinControl::create(
        -CAMERA_COORD_LIMIT, CAMERA_COORD_LIMIT, _camera->direction.z,
        2, 0.1f
    );
    _cameraDirectionZ->setPosition("cameraDirectionZLabel.right + 10", 115);
    _cameraDirectionZ->setSize(inputSize);
    _cameraDirectionZ->setWidgetName("cameraDirectionZ");
    _propertiesPanel->add(_cameraDirectionZ);
}

void CameraProperties::_initCameraFOV() {
    auto label = tgui::Label::create("Field of view:");
    label->setWidth(90);
    label->setPosition(0, "155 + (25 - height) / 2");

    _cameraFOV = tgui::SpinControl::create(0, 180, _camera->fov, 2, 0.1f);
    _cameraFOV->setSize("100% - 100", 25);
    _cameraFOV->setPosition("parent.right - width - 23", 155);
    _cameraFOV->setValue(_camera->fov);

    _propertiesPanel->add(label);
    _propertiesPanel->add(_cameraFOV);
}

void CameraProperties::_initScreen() {
    tgui::Layout2d inputSize = { "(parent.w - 243) / 3", 25 };
    auto labelX = tgui::Label::create("Screen:       w:");
    auto labelY = tgui::Label::create("h:");

    labelX->setWidth(100);
    labelX->setPosition(0, "195 + (25 - height) / 2");
    labelX->setWidgetName("screenWidthLabel");
    _propertiesPanel->add(labelX);

    _screenWidth = tgui::SpinControl::create(1, CAMERA_COORD_LIMIT, float(_camera->screen.size.width), 0, 1);
    _screenWidth->setPosition("screenWidthLabel.right", 195);
    _screenWidth->setSize(inputSize);
    _screenWidth->setWidgetName("screenWidth");
    _propertiesPanel->add(_screenWidth);

    labelY->setWidth(20);
    labelY->setPosition("screenWidth.right + 30", "195 + (25 - height) / 2");
    labelY->setWidgetName("screenHeightLabel");
    _propertiesPanel->add(labelY);

    _screenHeight = tgui::SpinControl::create(1, CAMERA_COORD_LIMIT, float(_camera->screen.size.height), 0, 1);
    _screenHeight->setPosition("screenHeightLabel.right + 10", 195);
    _screenHeight->setSize(inputSize);
    _screenHeight->setWidgetName("screenHeight");
    _propertiesPanel->add(_screenHeight);

    _resetButton = tgui::Button::create("Reset");
    _resetButton->getRenderer()->setTextSize(12);
    _resetButton->setSize(65, 20);
    _resetButton->setPosition("100% - width - 90", 197.5f);
    _resetButton->setEnabled(false);
    _resetButton->onClick([this]() {
        _onReset();
    });
    _propertiesPanel->add(_resetButton);

    _applyButton = tgui::Button::create("Apply");
    _applyButton->getRenderer()->setTextSize(12);
    _applyButton->setSize(80, 20);
    _applyButton->setPosition("100% - width", 197.5f);
    _applyButton->getRenderer()->setBackgroundColor("#0076c9");
    _applyButton->setEnabled(false);
    _applyButton->onClick([this]() {
        _onApply();
    });
    _propertiesPanel->add(_applyButton);
}

void CameraProperties::setEnabled(bool enabled) {
    auto changed = _configurationChanged();

    _propertiesPanel->setEnabled(enabled);
    _cameraName->setEnabled(enabled);
    _cameraPositionX->setEnabled(enabled);
    _cameraPositionY->setEnabled(enabled);
    _cameraPositionZ->setEnabled(enabled);
    _cameraDirectionX->setEnabled(enabled);
    _cameraDirectionY->setEnabled(enabled);
    _cameraDirectionZ->setEnabled(enabled);
    _cameraFOV->setEnabled(enabled);
    _screenWidth->setEnabled(enabled);
    _screenHeight->setEnabled(enabled);

    if (!enabled) {
        _applyButton->setEnabled(false);
        _resetButton->setEnabled(false);
    } else {
        _applyButton->setEnabled(changed);
        _resetButton->setEnabled(changed);
    }
}

void CameraProperties::_onApply() {
    _camera->direction = Raytracer::Common::Math::Vector3D(
        _cameraDirectionX->getValue(),
        _cameraDirectionY->getValue(),
        _cameraDirectionZ->getValue()
    );
    _camera->position = Raytracer::Common::Math::Point3D(
        _cameraPositionX->getValue(),
        _cameraPositionY->getValue(),
        _cameraPositionZ->getValue()
    );
    _camera->fov = _cameraFOV->getValue();
    _camera->screen.resize({
        size_t(_screenWidth->getValue()),
        size_t(_screenHeight->getValue())
    });
    _applyButton->setEnabled(false);
    _resetButton->setEnabled(false);
}

void CameraProperties::_onReset() {
    _cameraName->setText(_camera->name);
    _cameraPositionX->setValue(_camera->position.x);
    _cameraPositionY->setValue(_camera->position.y);
    _cameraPositionZ->setValue(_camera->position.z);
    _cameraDirectionX->setValue(_camera->direction.x);
    _cameraDirectionY->setValue(_camera->direction.y);
    _cameraDirectionZ->setValue(_camera->direction.z);
    _cameraFOV->setValue(_camera->fov);
    _screenWidth->setValue(float(_camera->screen.size.width));
    _screenHeight->setValue(float(_camera->screen.size.height));
    _applyButton->setEnabled(false);
    _resetButton->setEnabled(false);
}

bool CameraProperties::_configurationChanged() const {
    auto changed = false;

    changed |= _cameraName->getText() != _camera->name;
    changed |= _cameraPositionX->getValue() != _camera->position.x;
    changed |= _cameraPositionY->getValue() != _camera->position.y;
    changed |= _cameraPositionZ->getValue() != _camera->position.z;
    changed |= _cameraDirectionX->getValue() != _camera->direction.x;
    changed |= _cameraDirectionY->getValue() != _camera->direction.y;
    changed |= _cameraDirectionZ->getValue() != _camera->direction.z;
    changed |= _cameraFOV->getValue() != _camera->fov;
    changed |= _screenWidth->getValue() != float(_camera->screen.size.width);
    changed |= _screenHeight->getValue() != float(_camera->screen.size.height);

    return changed;
}

void CameraProperties::_initOnChangeEvents() {
    auto onChange = [this] {
        _applyButton->setEnabled(_configurationChanged());
        _resetButton->setEnabled(_configurationChanged());
    };

    _cameraName->onTextChange(onChange);
    _cameraPositionX->onValueChange(onChange);
    _cameraPositionY->onValueChange(onChange);
    _cameraPositionZ->onValueChange(onChange);
    _cameraDirectionX->onValueChange(onChange);
    _cameraDirectionY->onValueChange(onChange);
    _cameraDirectionZ->onValueChange(onChange);
    _cameraFOV->onValueChange(onChange);
    _screenWidth->onValueChange(onChange);
    _screenHeight->onValueChange(onChange);
}
