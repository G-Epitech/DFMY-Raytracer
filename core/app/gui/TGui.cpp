/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Backend.cpp
*/

#include <TGUI/Timer.hpp>
#include <thread>
#include "TGui.hpp"

using namespace Raytracer::Core::Gui;
using namespace tgui;

TGui::TGui(): Gui(), _requestedRenders(0) {}

TGui::~TGui() = default;

void TGui::mainLoop(tgui::Color clearColor)
{
    if (!m_window)
        return;

    m_backendRenderTarget->setClearColor(clearColor);

    const auto getTimerWakeUpTime = []{
        Optional<Duration> duration = Timer::getNextScheduledTime();
        if (duration && (*duration < std::chrono::milliseconds(10)))
            return *duration;
        else
            return Duration{std::chrono::milliseconds(10)};
    };

    setDrawingUpdatesTime(false);

    bool refreshRequired = true;
    std::chrono::steady_clock::time_point lastRenderTime;
    bool windowOpen = m_window->isOpen();
    while (m_window->isOpen()) {
        bool eventProcessed = false;
        while (true) {
            sf::Event event{};
            while (m_window->pollEvent(event)) {
                if (handleEvent(event))
                    eventProcessed = true;

                if (event.type == sf::Event::Closed) {
                    windowOpen = false;
                    eventProcessed = true;
                } else if ((event.type == sf::Event::Resized) || (event.type == sf::Event::MouseLeft)) {
                    eventProcessed = true;
                }
            }

            if (updateTime())
                break;

            _requestRenderMutex.lock();
            if (_requestedRenders > 0) {
                _requestedRenders -= 1;
                _requestRenderMutex.unlock();
                break;
            }
            _requestRenderMutex.unlock();

            if (eventProcessed || refreshRequired)
                break;

            std::this_thread::sleep_for(std::chrono::nanoseconds(getTimerWakeUpTime()));
        }

        if (!windowOpen)
            break;

        refreshRequired = true;

        const auto timePointNow = std::chrono::steady_clock::now();
        const auto timePointNextAllowed = lastRenderTime + std::chrono::milliseconds(15);
        if (timePointNextAllowed > timePointNow)
        {
            const auto timerWakeUpTime = getTimerWakeUpTime();
            if (timePointNextAllowed - timePointNow < timerWakeUpTime)
                std::this_thread::sleep_for(timePointNextAllowed - timePointNow);
            else
                std::this_thread::sleep_for(std::chrono::nanoseconds(timerWakeUpTime));

            continue;
        }

        m_backendRenderTarget->clearScreen();
        draw();
        m_window->display();

        refreshRequired = false;
        lastRenderTime = std::chrono::steady_clock::now();
    }
}

void TGui::requestRender() {
    _requestRenderMutex.lock();
    _requestedRenders += 1;
    _requestRenderMutex.unlock();
}
