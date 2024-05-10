/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** ConfigValidator
*/

#include "ConfigValidator.hpp"

const ConfigValidator::ValidatorFunction ConfigValidator::_validators[] = {
    &_materialsAreValid,
    &_camerasAreValid,
    &_objectsAreValid
};

void ConfigValidator::valid(const Config::SceneConfig &cfg)
{
    for (const auto& validator : _validators) {
        validator(cfg);
    }
}

void ConfigValidator::_materialsAreValid(const Config::SceneConfig &cfg)
{
    std::vector<Config::MaterialConfig> materials = cfg.materials;
    std::set<std::string> materialNames;

    for (const auto& material : materials) {
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
    std::vector<Config::CameraConfig> cameras = cfg.cameras;
    std::set<std::string> cameraNames;

    for (const auto& camera : cameras) {
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
    std::vector<Config::ObjectConfig> objects = cfg.objects;
    std::vector<Config::MaterialConfig> materials = cfg.materials;

    for (const auto& object : objects) {
        if (object.material.empty()) {
            throw ConfigException("object must have a material name");
        }
        if (std::find_if(materials.begin(), materials.end(),
            [object](const Config::MaterialConfig& material) {
                return material.name == object.material;
            }) == materials.end()) {
            throw ConfigException("object material \"" + object.material + "\" does not exist");
        }
    }
}
