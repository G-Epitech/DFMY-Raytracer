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

#define APP_DEFAULT_THREADS_COUNT 20
#define APP_DEFAULT_FORMAT "ppm"
#define APP_DEFAULT_PLUGINS_PATH "./plugins"
#define APP_DEFAULT_FRAMES_COUNT 15
#define APP_DEFAULT_RAYS_PER_PIXEL 15
#define APP_DEFAULT_RAY_BOUNCE 30

namespace Raytracer::Core {
    class App {
    public:
        /// @brief Options structure
        typedef struct Options {
            /// @brief GUI flag
            bool gui;
            /// @brief Help flag
            bool help;
            /// @brief Plugins path
            std::string pluginsPath;
            /// @brief Threads count
            size_t threadsCount;
            /// @brief Frames count
            size_t framesCount;
            /// @brief Rays per pixel
            size_t raysPerPixel;
            /// @brief Ray bounce
            size_t rayBounce;
            /// @brief Output format
            std::string outputFormat;
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
        Arguments _args = {
          .options = {
            .gui = false,
            .help = false,
            .pluginsPath = APP_DEFAULT_PLUGINS_PATH,
            .threadsCount = APP_DEFAULT_THREADS_COUNT,
            .framesCount = APP_DEFAULT_FRAMES_COUNT,
            .raysPerPixel = APP_DEFAULT_RAYS_PER_PIXEL,
            .rayBounce = APP_DEFAULT_RAY_BOUNCE,
            .outputFormat = APP_DEFAULT_FORMAT
          }
        };

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

        /**
         * @brief Read unsigned long argument
         * @param arg Argument value read from command line
         * @param value Value to set
         * @param name Name of the argument to set
         * @return Success status
         */
        [[nodiscard]]
        static bool _readULArg(const string &arg, size_t &value, const string &name);
    };
}
