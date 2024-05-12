/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CameraPanel.cpp
*/

#include "CameraPanel.hpp"

#include <utility>
#include "app/gui/GuiContext.hpp"

Raytracer::Core::Gui::CameraPanel::~CameraPanel() = default;

Raytracer::Core::Gui::CameraPanel::CameraPanel(
    Raytracer::Core::Rendering::Camera::Ptr &camera,
    Raytracer::Core::Gui::GuiContext &context,
    tgui::TabContainer::Ptr &tabContainer
) :
    _camera(camera),
    _context(context),
    _tabContainer(tabContainer),
    _propertiesPanel(_camera),
    _renderingSettingsPanel(context),
    _autoPaused(false)
{
    _panel = _tabContainer->addTab(_camera->name);
    _initRenderPanel();
    _initSettingsGroup();
}

void Raytracer::Core::Gui::CameraPanel::_initRenderPanel() {
    _renderPanel = tgui::Panel::create({"100%", "60%"});
    _renderPanel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    _renderPanel->getRenderer()->setBorders({0, 0, 0, 1});

    _frame = Raytracer::Core::Gui::RenderFrame::create();
    _panel->add(_renderPanel);
    _renderPanel->add(_frame);
}

void Raytracer::Core::Gui::CameraPanel::_initSettingsGroup() {
    _settingsGroup = tgui::Group::create({"100%", "40%"});
    _settingsGroup->setPosition(0, "60%");
    _settingsGroup->getRenderer()->setPadding(10);

    _propertiesPanel.init(_settingsGroup);
    _renderingSettingsPanel.init(_settingsGroup);
    _renderingSettingsPanel.renderButton->onClick([this] {
        _onRenderButtonClicked();
    });
    _renderingSettingsPanel.cancelButton->onClick([this] {
        _onCancelButtonClicked();
    });
    _panel->add(_settingsGroup);
}

void Raytracer::Core::Gui::CameraPanel::_render() {
    auto params = _renderingSettingsPanel.getComputeParams();

    _camera->compute(params, _context.app.scene->objects);
    auto progress = _camera->getComputeProgress();
    while (progress < 1) {
        _frame->updateFromScreen(_camera->screen);
        _context.gui.requestRender();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = _camera->getComputeProgress();
        if (_camera->getComputeStatus() == Rendering::Camera::ABORTED)
            break;
    }
    _camera->waitThreadsTeardown();
    _frame->updateFromScreen(_camera->screen);
    _context.gui.requestRender();
    _renderingSettingsPanel.renderButton->setText("Render");
    _propertiesPanel.setEnabled(true);
    _renderingSettingsPanel.setRenderingSensitiveEnabled(true);
}

void Raytracer::Core::Gui::CameraPanel::_onRenderButtonClicked() {
    if (_camera->getComputeStatus() == Rendering::Camera::RUNNING) {
        _renderingSettingsPanel.renderButton->setText("Resume rendering");
        _camera->pauseCompute();
    } else if (_camera->getComputeStatus() == Rendering::Camera::PAUSED) {
        _camera->resumeCompute();
        _renderingSettingsPanel.renderButton->setText("Pause rendering");
        return;
    } else {
        _propertiesPanel.setEnabled(false);
        _renderingSettingsPanel.setRenderingSensitiveEnabled(false);
        _renderingSettingsPanel.renderButton->setText("Pause rendering");
        if (_camera->getComputeStatus() > 0) {
            _camera->cancelCompute();
            _camera->waitThreadsTeardown();
        }
        _renderingThread = std::thread(&CameraPanel::_render, this);
        _renderingThread.detach();
    }
}

void Raytracer::Core::Gui::CameraPanel::_onCancelButtonClicked() {
    _propertiesPanel.setEnabled(false);
    _renderingSettingsPanel.setRenderingSensitiveEnabled(false);
    _camera->cancelCompute();
    _camera->waitFinished();
    _propertiesPanel.setEnabled(true);
    _renderingSettingsPanel.setRenderingSensitiveEnabled(true);
    _renderingSettingsPanel.renderButton->setText("Render");
}

void Raytracer::Core::Gui::CameraPanel::onTabSelected() {
    if (_autoPaused) {
        _autoPaused = false;
        _camera->resumeCompute();
        return;
    }
}

void Raytracer::Core::Gui::CameraPanel::onTabUnselected() {
    if (_camera->getComputeStatus() == Rendering::Camera::RUNNING) {
        _camera->pauseCompute();
        _autoPaused = true;
    }
}
