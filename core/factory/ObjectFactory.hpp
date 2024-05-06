/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjectFactory.hpp
*/

#pragma once

#include <string>
#include <map>
#include "interfaces/IObject.hpp"
#include "interfaces/IObjectProvider.hpp"

namespace Raytracer::Core {
    using namespace Raytracer::Common;

    class ObjectFactory {
    public:
        /**
         * @brief Exception class for ObjectFactory
         */
        class Exception;
        /**
         * @brief Construct a new ObjectFactory object
         * @param pluginsDir Directory where the plugins are stored
         */
        explicit ObjectFactory(const std::string &pluginsDir = "./plugins");

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
            const Graphics::Material::Ptr &material,
            const Math::Point3D &position,
            const Raytracer::Common::ObjectProperty &property
        );

    private:
        /// @brief Map of object providers
        std::map<std::string, Common::IObjectProvider::Ptr> _providers;
    };

    class ObjectFactory::Exception : public std::exception {
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
