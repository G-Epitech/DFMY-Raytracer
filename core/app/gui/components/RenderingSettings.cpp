/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RenderingSettings.cpp
*/

#include "RenderingSettings.hpp"
#include "types/rendering/Camera.hpp"

using namespace Raytracer::Core::Gui;

RenderingSettings::~RenderingSettings() = default;

RenderingSettings::RenderingSettings(GuiContext &context) : _context(context) {}

void RenderingSettings::init(tgui::Group::Ptr &settingsGroup) {
    auto label = tgui::Label::create("Rendering");
    label->getRenderer()->setTextSize(15);
    label->getRenderer()->setTextStyle("medium");

    _settingsPanel = tgui::Panel::create();
    _settingsPanel->setPosition("60% + 10", 0);
    _settingsPanel->setSize("40% - 10", "100%");
    _settingsPanel->getRenderer()->setPadding(10);
    _settingsPanel->add(label);

    _initInputs();
    _initButtons();

    settingsGroup->add(_settingsPanel);
}

void RenderingSettings::_initInputs() {
    auto label = tgui::Label::create("Threads :");
    label->setWidth(150);
    label->setPosition(0, "35 + (25 - height) / 2");

    _threadsCount = tgui::SpinControl::create(1, 64, float(_context.app.args.options.threadsCount), 0, 1);
    _threadsCount->setSize("100% - 150", 25);
    _threadsCount->setPosition(150, 35);

    _settingsPanel->add(label);
    _settingsPanel->add(_threadsCount);

    label = tgui::Label::create("Additional frames :");
    label->setWidth(150);
    label->setPosition(0, "70 + (25 - height) / 2");

    _additionalFrames = tgui::SpinControl::create(0, 64, float(_context.app.args.options.additionalFramesCount), 0, 1);
    _additionalFrames->setSize("100% - 150", 25);
    _additionalFrames->setPosition(150, 70);
    _settingsPanel->add(label);
    _settingsPanel->add(_additionalFrames);

    label = tgui::Label::create("Rays per pixel :");
    label->setWidth(150);
    label->setPosition(0, "105 + (25 - height) / 2");

    _raysPerPixel = tgui::SpinControl::create(1, 64, float(_context.app.args.options.raysPerPixel), 0, 1);
    _raysPerPixel->setSize("100% - 150", 25);
    _raysPerPixel->setPosition(150, 105);
    _settingsPanel->add(label);
    _settingsPanel->add(_raysPerPixel);

    label = tgui::Label::create("Max ray bounce :");
    label->setWidth(150);
    label->setPosition(0, "140 + (25 - height) / 2");

    _maxRayBounce = tgui::SpinControl::create(1, 64, float(_context.app.args.options.rayBounce), 0, 1);
    _maxRayBounce->setSize("100% - 150", 25);
    _maxRayBounce->setPosition(150, 140);
    _settingsPanel->add(label);
    _settingsPanel->add(_maxRayBounce);
}

void RenderingSettings::_initButtons() {
    saveButton = tgui::Button::create("Save");
    saveButton->setSize("100%", 20);
    saveButton->setPosition(0, "100% - 20");
    saveButton->setWidgetName("renderingSaveButton");
    _settingsPanel->add(saveButton);

    renderButton = tgui::Button::create("Render");
    renderButton->setSize("65% - 10", 30);
    renderButton->setPosition(0, "renderingSaveButton.top - height - 10");
    renderButton->getRenderer()->setBackgroundColor("#0076c9");
    _settingsPanel->add(renderButton);

    cancelButton = tgui::Button::create("Cancel");
    cancelButton->setSize("35% - 10", 30);
    cancelButton->setEnabled(false);
    cancelButton->setPosition("65% + 10", "renderingSaveButton.top - height - 10");
    _settingsPanel->add(cancelButton);
}

Raytracer::Core::Rendering::Camera::ComputeParams RenderingSettings::getComputeParams() const {
    return {
        .threads = static_cast<unsigned int>(_threadsCount->getValue()),
        .additionalFrames = static_cast<unsigned int>(_additionalFrames->getValue()),
        .raysPerPixel = static_cast<unsigned int>(_raysPerPixel->getValue()),
        .rayBounceLimit = static_cast<unsigned int>(_maxRayBounce->getValue())
    };
}

void RenderingSettings::setRenderingSensitiveEnabled(bool enabled) {
    _threadsCount->setEnabled(enabled);
    _additionalFrames->setEnabled(enabled);
    _raysPerPixel->setEnabled(enabled);
    _maxRayBounce->setEnabled(enabled);
    saveButton->setEnabled(enabled);
    cancelButton->setEnabled(!enabled);
}
