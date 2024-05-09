/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** App.hpp
*/

#pragma once

#include <vector>
#include <string>
#include "plugins/PluginsManager.hpp"
#include "types/rendering/Scene.hpp"

namespace Raytracer::Core {
    class App {
    public:
        /// @brief Options structure
        typedef struct Options {
            /// @brief GUI flag
            bool gui = false;
            /// @brief Help flag
            bool help = false;
            /// @brief Plugins path
            std::string pluginsPath = "./plugins";
            /// @brief Threads count
            size_t threadsCount = 8;
            /// @brief Output format
            std::string outputFormat = "ppm";
        } Options;

        /// @brief Arguments structure
        typedef struct Arguments {
            /// @brief Scene file path
            std::vector<std::string> scenes;
            /// @brief Options
            Options options;
        } Arguments;

        /// @brief App context
        struct Context {
            /// @brief Scene
            Rendering::Scene::Ptr scene;
            /// @brief Plugins manager
            PluginsManager &pluginsManager;
            /// @brief Arguments
            Arguments &args;
        };

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

        /**
        * @brief Load a scene
        * @param scenePath Scene file path
        * @return Success status of the operation
        */
        bool tryLoadScene(const std::string &scenePath);

    private:
        /// @brief Application arguments
        Arguments _args;

        /// @brief Plugins manager
        PluginsManager _pluginsManager;

        /// @brief Current scene
        Rendering::Scene::Ptr _scene;

        /**
         * @brief Read arguments
         * @param argc Number of arguments
         * @param argv Argument values
         * @return Success status
         */
        bool _readArgs(int argc, char **argv);

        /**
         * @brief Read unsigned long argument
         * @param arg Argument value
         * @param value Value to set
         * @return Success status
         */
        [[nodiscard]]
        static bool _readUL(const std::string& arg, size_t &value);

        /**
         * @brief Parse options
         * @param argc Number of arguments
         * @param argv Argument values
         * @return Success status
         */
        bool _readOptions(int argc, char **argv);

        /**
         * @brief Load plugins
         * @return Success status of the operation
         */
        bool _loadPlugins();

        /**
         * @brief Launch the handler
         */
        int _runHandler();

        /**
         * @brief Read output format
         * @param arg Argument value
         * @param outputFormat Output format
         * @return Success status
         */
        [[nodiscard]]
        static bool _readOutputFormat(const std::string &arg, std::string &outputFormat);
    };
}
