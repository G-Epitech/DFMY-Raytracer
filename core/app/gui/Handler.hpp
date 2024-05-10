/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.hpp
*/

#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "app/IHandler.hpp"
#include "app/gui/components/Form.hpp"
#include "GuiContext.hpp"

namespace Raytracer::Core::Gui {
    class Handler : public IHandler {
    public:
        /**
         * @brief Create a new GUI handler
         * @param context Application context
         */
        explicit Handler(App::Context &context);

        /**
         * @brief Default destructor
         */
        ~Handler() override;

        /**
         * @brief Run the handler
         */
        int run() override;

    private:
        /// @brief Application arguments received from App
        App::Context &_appContext;

        /// @brief SFML window
        sf::RenderWindow _window;

        /// @brief Gui context
        GuiContext _context;

        /// @brief Icon of the window
        sf::Image _icon;

        /// @brief Form
        Form _form;

        /**
         * @brief Initialize the GUI
         */
        void _initGui();
    };
}
