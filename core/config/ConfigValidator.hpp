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
        ConfigValidator() = default;
        ~ConfigValidator() = default;

        typedef std::function<void(const Config::SceneConfig&)> ValidatorFunction;

        static void sceneIsValid(const Config::SceneConfig &cfg);

        static void _materialsAreValid(const Config::SceneConfig &cfg);
        static void _camerasAreValid(const Config::SceneConfig &cfg);
        static void _objectsAreValid(const Config::SceneConfig &cfg);
};

