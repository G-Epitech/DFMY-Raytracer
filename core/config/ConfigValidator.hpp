/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ConfigValidator
*/

#pragma once

#include <set>
#include "Config.hpp"

using namespace Raytracer::Core;

namespace Raytracer::Core {
    class ConfigValidator;
};

class Raytracer::Core::ConfigValidator {
    public:
        ConfigValidator() = default;
        ~ConfigValidator() = default;

        static void sceneIsValid(const Config::SceneConfig &cfg);

    private:
        static void _materialsAreValid(const std::list<Config::MaterialConfig> materials);
};
