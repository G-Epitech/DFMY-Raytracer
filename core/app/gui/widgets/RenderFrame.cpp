/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RenderFrame.cpp
*/

#include <memory>
#include <TGUI/TGUI.hpp>
#include "RenderFrame.hpp"

using namespace Raytracer::Core::Gui;

RenderFrame::RenderFrame(const char *typeName, bool initRenderer) : Widget(typeName, initRenderer) {
    _sprite.setTexture(_texture);
}

RenderFrame::Ptr RenderFrame::create() {
    auto frame = std::make_shared<RenderFrame>();

    frame->setSize("100%", "100%");
    return frame;
}

void RenderFrame::draw(tgui::BackendRenderTarget &target, tgui::RenderStates states) const {
    const auto size = getSize();
    auto textureSize = _texture.getImageSize();
    auto sizeRatio = size.x / size.y;
    auto textureRatio = float(textureSize.x) / float(textureSize.y);
    auto scale = sizeRatio > textureRatio
                        ? size.y / float(textureSize.y)
                        : size.x / float(textureSize.x);
    tgui::Vector2f scaled = {
        float(textureSize.x) * scale,
        float(textureSize.y) * scale
    };
    tgui::Vector2f offset = {
        (size.x - scaled.x) / 2,
        (size.y - scaled.y) / 2
    };

    states.transform.translate(offset);
    states.transform.scale({scale, scale});
    target.drawSprite(states, _sprite);
}

bool RenderFrame::isMouseOnWidget(tgui::Vector2f pos) const {
    return false;
}

tgui::Widget::Ptr RenderFrame::clone() const {
    return std::make_shared<RenderFrame>(*this);
}

void RenderFrame::updateFromScreen(Raytracer::Core::Rendering::Screen &screen) {
    _texture.loadFromPixelData({
        (unsigned int) (screen.size.width),
        (unsigned int) (screen.size.height)
        },
        screen.getPixels().get()
    );
    _sprite.setTexture(_texture);
}

RenderFrame::~RenderFrame() = default;
