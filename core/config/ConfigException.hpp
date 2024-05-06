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
        explicit ConfigException(std::string const &message);

        const char *what() const noexcept override;
        const std::string &getMessage() const;
    private:
        std::string _message;
};
