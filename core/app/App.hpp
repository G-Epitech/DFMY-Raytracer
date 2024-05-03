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

        /**
         * @brief Print help message
         * @return Program exit code
         */
        static int help();

    private:
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

        /// @brief List of scenes
        std::vector<std::string> _scenes;

        /**
         * @brief Read arguments
         * @param argc Number of arguments
         * @param argv Argument values
         * @param args Arguments structure in which to store the parsed arguments
         * @return Success status
         */
        static bool _readArgs(int argc, char **argv, App::Arguments &args);

        /**
         * @brief Parse options
         * @param argc Number of arguments
         * @param argv Argument values
         * @param options Options structure in which to store the parsed options
         * @return Success status
         */
         static bool _readOptions(int argc, char **argv, App::Options &options);
    };
}
