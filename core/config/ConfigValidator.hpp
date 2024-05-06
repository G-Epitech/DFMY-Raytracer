/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ConfigValidator
*/

#pragma once

#include <set>
#include <functional>
#include "Config.hpp"

using namespace Raytracer::Core;

namespace Raytracer::Core {
    class ConfigValidator;
};

class Raytracer::Core::ConfigValidator {
    public:
        /// @brief Validate a scene configuration
        ConfigValidator() = default;
        ~ConfigValidator() = default;

        /// @brief Validate a scene configuration
        static void sceneIsValid(const Config::SceneConfig &cfg);

    private:
        /// @brief Validate materials
        static void _materialsAreValid(const Config::SceneConfig &cfg);
        /// @brief Validate cameras
        static void _camerasAreValid(const Config::SceneConfig &cfg);
        /// @brief Validate objects
        static void _objectsAreValid(const Config::SceneConfig &cfg);

        /// @brief Type of a validation function
        typedef std::function<void(const Config::SceneConfig&)> ValidatorFunction;
        /// @brief List of validation functions
        static const ValidatorFunction _validators[];
};

