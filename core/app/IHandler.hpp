/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IHandler.hpp
*/

#pragma once

#include "App.hpp"

namespace Raytracer::Core {
    class IHandler {
    public:
        /**
         * @brief Default destructor
         */
        virtual ~IHandler() = default;

        /**
         * @brief Run the handler
         */
        virtual int run() = 0;
    };
}
