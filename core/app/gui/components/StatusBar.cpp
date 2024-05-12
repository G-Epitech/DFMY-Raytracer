/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** StatusBar.cpp
*/

#include "StatusBar.hpp"
#include "app/gui/GuiContext.hpp"

using namespace Raytracer::Core::Gui;

StatusBar::StatusBar(GuiContext &context) : _context(context) {}

void StatusBar::init() {
    _layout = tgui::HorizontalLayout::create();

    _layout->setSize("100%", 20);
    _layout->setPosition(0, "&.height - height");
    _layout->setTextSize(13);

    _left = tgui::Panel::create();
    _left->setSize("50%", "100%");
    _left->getRenderer()->setBorders(0);
    _left->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    _layout->add(_left);

    _right = tgui::Panel::create();
    _right->getRenderer()->setBorders(0);
    _right->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    _right->setSize("50%", "100%");
    _layout->add(_right);

    statusLabel = tgui::Label::create();
    statusLabel->setText("Ready");
    statusLabel->setTextSize(13);
    statusLabel->setPosition(0, "(parent.height - height) / 2");
    statusLabel->setWidgetName("statusLabel");
    _left->add(statusLabel);

    progressBar = tgui::ProgressBar::create();
    progressBar->setSize("20%", 10);
    progressBar->setPosition("statusLabel.right + 10", "(parent.height - height) / 2");
    progressBar->setVisible(false);
    progressBar->setWidgetName("statusProgressBar");
    progressBar->getRenderer()->setFillColor("#0076c9");
    _left->add(progressBar);

    _context.gui.add(_layout);
}

StatusBar::Ptr StatusBar::create(GuiContext &context) {
    return std::make_shared<StatusBar>(context);
}

StatusBar::~StatusBar() = default;
