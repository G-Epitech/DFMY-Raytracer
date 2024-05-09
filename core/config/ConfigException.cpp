/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** ConfigException
*/

#include "ConfigException.hpp"

Raytracer::Core::ConfigException::ConfigException(std::string const &message)
    : _message("Configuration error: " + message) {}

const char *Raytracer::Core::ConfigException::what() const noexcept
{
    return _message.c_str();
}

const std::string &Raytracer::Core::ConfigException::getMessage() const
{
    return _message;
}
