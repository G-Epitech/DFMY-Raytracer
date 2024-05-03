/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** App.hpp
*/

#pragma once
namespace Raytracer::Core {
    class App {
    public:
        /// @brief Default constructor
        App() = default;
        ~App() = default;

        /**
         * @brief Run the application
         * @param argc Number of arguments
         * @param argv Value of arguments
         * @return Program exit code
         */
        int run(int argc, char **argv);
    };
}
