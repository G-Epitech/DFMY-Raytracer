/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CameraPanel.cpp
*/

#include "CameraPanel.hpp"

#include "app/gui/GuiContext.hpp"
#include "types/graphics/Image.hpp"

Raytracer::Core::Gui::CameraPanel::~CameraPanel() {
    _camera->cancelCompute();
    _camera->waitThreadsTeardown();
    if (_renderingThread.joinable())
        _renderingThread.join();
}

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
    _renderingSettingsPanel.saveButton->setEnabled(false);
    _renderingSettingsPanel.saveButton->onClick([this] {
        _onSaveButtonClicked();
    });
    _panel->add(_settingsGroup);
}

void Raytracer::Core::Gui::CameraPanel::_render() {
    auto params = _renderingSettingsPanel.getComputeParams();

    _camera->compute(params, _context.app.scene->objects);
    auto progress = _camera->getComputeProgress();
    auto status = _camera->getComputeStatus();

    while (progress < 1) {
        _frame->updateFromScreen(_camera->screen);
        _context.gui.requestRender();

        progress = _camera->getComputeProgress();
        status = _camera->getComputeStatus();

        if (status == Rendering::Camera::RUNNING)
            _updateStatusBar();
        else if (status != Rendering::Camera::PAUSED)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    _frame->updateFromScreen(_camera->screen);
    _context.gui.requestRender();
    _camera->waitThreadsTeardown();

    _updateStatusBar();
    _renderingSettingsPanel.renderButton->setText("Render");
    _propertiesPanel.setEnabled(true);
    _renderingSettingsPanel.setRenderingSensitiveEnabled(true);
}

void Raytracer::Core::Gui::CameraPanel::_onRenderButtonClicked() {
    if (_camera->getComputeStatus() == Rendering::Camera::RUNNING) {
        _renderingSettingsPanel.renderButton->setText("Resume rendering");
        _camera->pauseCompute();
        _updateStatusBar();
    } else if (_camera->getComputeStatus() == Rendering::Camera::PAUSED) {
        _camera->resumeCompute();
        _renderingSettingsPanel.renderButton->setText("Pause rendering");
        _updateStatusBar();
    } else {
        _propertiesPanel.setEnabled(false);
        _renderingSettingsPanel.setRenderingSensitiveEnabled(false);
        _renderingSettingsPanel.renderButton->setText("Pause rendering");
        if (_camera->getComputeStatus() > 0) {
            _camera->cancelCompute();
            _camera->waitThreadsTeardown();
        }
        if (_renderingThread.joinable())
            _renderingThread.join();
        _renderingThread = std::thread(&CameraPanel::_render, this);
    }
}

void Raytracer::Core::Gui::CameraPanel::_onCancelButtonClicked() {
    _propertiesPanel.setEnabled(false);
    _renderingSettingsPanel.setRenderingSensitiveEnabled(false);
    _camera->cancelCompute();
    _camera->waitThreadsTeardown();
    _propertiesPanel.setEnabled(true);
    _renderingSettingsPanel.setRenderingSensitiveEnabled(true);
    _renderingSettingsPanel.renderButton->setText("Render");
    _updateStatusBar();
}

void Raytracer::Core::Gui::CameraPanel::onTabSelected() {
    if (_autoPaused) {
        _autoPaused = false;
        _camera->resumeCompute();
    }
    _updateStatusBar();
}

void Raytracer::Core::Gui::CameraPanel::onTabUnselected() {
    if (_camera->getComputeStatus() == Rendering::Camera::RUNNING) {
        _camera->pauseCompute();
        _autoPaused = true;
    }
}

void Raytracer::Core::Gui::CameraPanel::_updateStatusBar() {
    auto progressBar = _context.statusBar->progressBar;
    auto statusLabel = _context.statusBar->statusLabel;
    auto progressValue = (unsigned int)(_camera->getComputeProgress() * 100);

    switch (_camera->getComputeStatus()) {
        case Rendering::Camera::RUNNING:
            progressBar->setVisible(true);
            progressBar->setValue(progressValue);
            statusLabel->setText("Rendering: " + std::to_string(progressValue) + "% done");
            break;
        case Rendering::Camera::PAUSED:
            progressBar->setVisible(true);
            progressBar->setValue(progressValue);
            statusLabel->setText("Rendering paused");
            break;
        default:
            progressBar->setVisible(false);
            statusLabel->setText("Ready");
            break;
    }
}

void Raytracer::Core::Gui::CameraPanel::_onSaveButtonClicked() {
    auto fileBrowser = tgui::FileDialog::create("Save file", "Save", true);

    fileBrowser->setCancelButtonText("Cancel");
    fileBrowser->setMultiSelect(false);
    fileBrowser->setFileMustExist(false);
    fileBrowser->setFilename(_context.app.scene->name + " - " + _camera->name);
    fileBrowser->setFileTypeFilters({
        {"Portable Network Graphics", {"*.png"}},
        {"JPEG Image", {"*.jpg", "*.jpeg"}},
        {"Bitmap Image", {"*.bmp"}},
        {"Portable Pixmap Image", {"*.ppm"}},
        {"All files", {"*"}}
    });

    fileBrowser->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
    fileBrowser->onFileSelect([this, fileBrowser](const tgui::String& selectedFile) {
        std::string file = selectedFile.toStdString();
        auto filterIndex = fileBrowser->getFileTypeFiltersIndex();
        auto filterFormats = fileBrowser->getFileTypeFilters()[filterIndex].second;
        auto filter = filterFormats.empty() ? "" : filterFormats.front().toStdString();

        tgui::Timer::scheduleCallback([this, file, filter] {
            _saveImage(file, filter);
        });
    });
    fileBrowser->onClose([this] {
        _renderingSettingsPanel.saveButton->setEnabled(true);
    });
    _renderingSettingsPanel.saveButton->setEnabled(false);
    _context.gui.add(fileBrowser);
}

void Raytracer::Core::Gui::CameraPanel::_saveImage(string filename, const string& filter)
{
    auto ext = filename.substr(filename.find_last_of('.') + 1);
    auto filterExtension = filter.substr(filter.find_last_of('.') + 1);
    auto &screen = _camera->screen;
    std::vector<string> validExtensions = {"png", "jpg", "jpeg", "bmp", "ppm"};

    if (ext.empty() || (ext != filterExtension && !filterExtension.empty())) {
        filename += ".";
        filename += filterExtension;
    }
    if (std::find(validExtensions.begin(), validExtensions.end(), filterExtension) == validExtensions.end()) {
        auto messageBox = tgui::MessageBox::create("Error", "Invalid file extension", {"OK"});

        messageBox->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
        messageBox->setWidth(300);
        messageBox->onButtonPress([this, messageBox] {
            _context.gui.remove(messageBox);
        });
        _context.gui.add(messageBox);
        return;
    }
    Raytracer::Core::Graphics::Image image(screen.size.width, screen.size.height, screen.getPixels());
    _context.statusBar->statusLabel->setText("Saving: " + filename);
    if (image.saveTo(filename))
        _context.statusBar->statusLabel->setText("Saved to:" + filename);
    else
        _context.statusBar->statusLabel->setText("Error while saving image");
}
