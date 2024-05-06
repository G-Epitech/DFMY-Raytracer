/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** App.hpp
*/

#pragma once

#include <vector>
#include <string>

namespace Raytracer::Core {
    class App {
    public:
        /// @brief Options structure
        typedef struct Options {
            /// @brief GUI flag
            bool gui = false;
            /// @brief Help flag
            bool help = false;
        } Options;

        /// @brief Arguments structure
        typedef struct Arguments {
            /// @brief Scene file path
            std::vector<std::string> scenes;
            /// @brief Options
            Options options;
        } Arguments;

        /**
         * @brief Default constructor
         */
        App() = default;

        /**
         * @brief Default destructor
         */
        ~App() = default;

        /**
         * @brief Run the application
         * @param argc Number of arguments
         * @param argv Value of arguments
         * @return Program exit code
         */
        int run(int argc, char **argv);

        /**
         * @brief Print help message
         * @return Program exit code
         */
        static int help();

    private:
        /// @brief Application arguments
        Arguments _args;

        /**
         * @brief Read arguments
         * @param argc Number of arguments
         * @param argv Argument values
         * @return Success status
         */
        bool _readArgs(int argc, char **argv);

        /**
         * @brief Parse options
         * @param argc Number of arguments
         * @param argv Argument values
         * @return Success status
         */
         bool _readOptions(int argc, char **argv);
    };
}
