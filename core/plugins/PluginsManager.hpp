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
         * @brief Exception class for invalid path
         */
        class InvalidPathException;

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
         * @throw InvalidPathException If the path is invalid (not found, not a directory...)
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

    class PluginsManager::InvalidPathException : public Exception {
    public:
        enum class Reason {
            NOT_FOUND,
            NOT_DIRECTORY
        };
        /**
         * @brief Construct a new InvalidPathException object
         * @param message Message of the exception
         */
        explicit InvalidPathException(const std::string &path, Reason reason);

        /**
         * @brief Get the path that caused the exception
         * @return Path that caused the exception
         */
        [[nodiscard]]
        const char *path() const noexcept;

        /**
         * @brief Get the reason of the exception
         * @return Reason of the exception
         */
        [[nodiscard]]
        Reason reason() const noexcept;

    private:
        /// @brief Path that caused the exception
        std::string _path;

        /// @brief Reason of the exception
        Reason _reason;
    };
}
