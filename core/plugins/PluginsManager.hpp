/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PluginsManager.hpp
*/

#pragma once

#include <string>
#include <map>
#include <list>
#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"
#include "libs/DLLoader/DLLoader.hpp"

namespace Raytracer::Core {
    using namespace Raytracer::Common;

    class PluginsManager {
    public:
        /**
         * @brief Exception class for ObjectFactory
         */
        class Exception;
        /**
         * @brief Construct a new ObjectFactory object
         */
        PluginsManager();

        /**
         * @brief Destroy the ObjectFactory object
         */
        ~PluginsManager();

        /**
         * @brief Load the plugins from the given path
         * @param pluginsDir Path to the plugins directory
         */
        void load(const std::string& pluginsDir = "./plugins");

        /// @brief Map of object providers
        std::map<std::string, IObjectProvider::Ptr> providers;

    private:
        /// @brief Map of plugins loaders
        std::list<DLLoader::Ptr> _loaders;

        /**
         * @brief Register a plugin library
         * @param filepath Path to the plugin library
         */
        void _loadPlugin(const std::string& filepath);

        /**
         * @brief Register a plugin
         * @param provider Loader of the plugin
         */
        void _registerPlugin(IObjectProvider::Ptr provider);
    };

    class PluginsManager::Exception : public std::exception {
    public:
        /**
         * @brief Construct a new Exception object
         * @param message Message of the exception
         */
        explicit Exception(std::string message);

        /**
         * @brief Get the message of the exception
         * @return Message of the exception
         */
        [[nodiscard]]
        const char *what() const noexcept override;

    private:
        /// @brief Message of the exception
        std::string _message;
    };
}
