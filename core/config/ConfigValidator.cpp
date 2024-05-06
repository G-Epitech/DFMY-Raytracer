/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ConfigValidator
*/

#include "ConfigValidator.hpp"

void ConfigValidator::sceneIsValid(const Config::SceneConfig &cfg)
{
    _materialsAreValid(cfg.materials);
}

void ConfigValidator::_materialsAreValid(const std::list<Config::MaterialConfig> materials)
{
    std::set<std::string> materialNames;

    for (auto material : materials) {
        if (material.reflectivity < 0 || material.reflectivity > 1) {
            throw ConfigException(material.name + " reflectivity must be between 0 and 1");
        }
        if (materialNames.find(material.name) != materialNames.end()) {
            throw ConfigException("material name \"" + material.name + "\" is already used");
        }
        materialNames.insert(material.name);
    }
}
