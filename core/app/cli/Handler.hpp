/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CliHandler.hpp
*/

#pragma once

#include "app/IHandler.hpp"
#include "app/App.hpp"

namespace Raytracer::Core::Cli {
    class Handler : public IHandler {
    public:
        /**
         * @brief Create a new cli handler
         * @param args Application arguments
         */
        explicit Handler(App::Arguments &args);

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
        App::Arguments &_args;
    };
}
