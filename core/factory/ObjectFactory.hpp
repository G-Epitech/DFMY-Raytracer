/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjectFactory.hpp
*/

#pragma once

#include "plugins/PluginsManager.hpp"

namespace Raytracer::Core {
    class ObjectFactory {
    public:

        /// @brief Exception class for ObjectFactory
        class Exception;

        /**
         * @brief Construct a new ObjectFactory object
         * @param pluginsManager Plugins manager to use to create objects
         */
        explicit ObjectFactory(PluginsManager &pluginsManager);

        /**
         * @brief Destroy the ObjectFactory object
         */
        ~ObjectFactory();

        /**
         * @brief Create a new object
         * @param name Name of the object
         * @param material Material of the object
         * @param position Position of the object
         * @param property Property of the object
         * @return Shared pointer to the new object
         */
        IObject::Ptr create(
            const std::string &name,
            const std::string &type,
            const Common::Graphics::Material::Ptr &material,
            const Math::Vector3D &rotation,
            const Math::Point3D &position,
            const ObjectProperty &property
        );

    private:
        /// @brief Plugins manager to use to create objects
        PluginsManager &_pluginsManager;
    };

    class ObjectFactory::Exception : public std::exception {
    public:
        /**
         * @brief Construct a new Exception object
         * @param message Error message
         */
        explicit Exception(std::string message);

        /**
         * @brief Get the error message
         * @return Error message
         */
        [[nodiscard]]
        const char *what() const noexcept override;

    private:
        /// @brief Error message
        std::string _message;
    };
}
