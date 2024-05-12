/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Backend.hpp
*/

#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Raytracer::Core::Gui {
    class TGui: public tgui::Gui {
    public:
        /**
         * @brief Create a new backend
         */
        TGui();

        /**
         * @brief Destroy the backend
         */
        ~TGui() override;

        void mainLoop(tgui::Color clearColor) override;

        /**
         * @brief Request a render
         */
        void requestRender();

    private:
        /// @brief Render requested
        size_t _requestedRenders;
        /// @brief Render mutex
        std::mutex _requestRenderMutex;
    };
}