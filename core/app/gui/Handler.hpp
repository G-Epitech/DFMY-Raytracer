/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.hpp
*/

#pragma once

#include "app/IHandler.hpp"

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
    };
}
