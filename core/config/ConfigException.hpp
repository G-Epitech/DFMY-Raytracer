/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** ConfigException
*/

#pragma once

#include <exception>
#include <string>

namespace Raytracer::Core {
    class ConfigException;
};

class Raytracer::Core::ConfigException : public std::exception {
    public:
        /**
         * @brief Construct a new ConfigException object
         * @param message Message of the exception
         */
        explicit ConfigException(std::string const &message);

        /**
         * @brief Get the error message
         * @return Error message
         */
        [[nodiscard]]
        const char *what() const noexcept override;

        /**
         * @brief Get the error message as a string
         * @return Error message
         */
        [[nodiscard]]
        const std::string &getMessage() const;
    private:
        std::string _message;
};
