/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ConfigValidator
*/

#include "ConfigValidator.hpp"

static const ConfigValidator::ValidatorFunction _validators[] = {
    ConfigValidator::_materialsAreValid,
    ConfigValidator::_camerasAreValid,
    ConfigValidator::_objectsAreValid
};

void ConfigValidator::sceneIsValid(const Config::SceneConfig &cfg)
{
    for (auto validator : _validators) {
        validator(cfg);
    }
}

void ConfigValidator::_materialsAreValid(const Config::SceneConfig &cfg)
{
    std::list<Config::MaterialConfig> materials = cfg.materials;
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

void ConfigValidator::_camerasAreValid(const Config::SceneConfig &cfg)
{
    std::list<Config::CameraConfig> cameras = cfg.cameras;
    std::set<std::string> cameraNames;

    for (auto camera : cameras) {
        if (camera.fov < 0 || camera.fov > 180) {
            throw ConfigException(camera.name + " fov must be between 0 and 180");
        }
        if (cameraNames.find(camera.name) != cameraNames.end()) {
            throw ConfigException("camera name \"" + camera.name + "\" is already used");
        }
        cameraNames.insert(camera.name);
    }
}

void ConfigValidator::_objectsAreValid(const Config::SceneConfig &cfg)
{
    std::list<Config::ObjectConfig> objects = cfg.objects;
    std::list<Config::MaterialConfig> materials = cfg.materials;

    for (auto object : objects) {
        if (object.material.empty()) {
            throw ConfigException("object must have a material name");
        }
        if (std::find_if(materials.begin(), materials.end(),
            [object](Config::MaterialConfig material) {
                return material.name == object.material;
            }) == materials.end()) {
            throw ConfigException("object material \"" + object.material + "\" does not exist");
        }
    }
}
