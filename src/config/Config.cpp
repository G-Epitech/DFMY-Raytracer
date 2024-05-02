/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** Config
*/

#include "Config.hpp"

Config::Config()
{
}

scene_config_t Config::load(const std::string &path)
{
    scene_config_t scene_config;
    libconfig::Config cfg;

    try {
        cfg.readFile(path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        throw Config::Exception("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        throw Config::Exception("Parse error at " + std::to_string(pex.getLine())
            + ": " + pex.getError() + " - " + pex.getFile());
    }
    const libconfig::Setting &root = cfg.getRoot();
    scene_config.cameras = _loadCameras(root);
    return scene_config;
}

std::list<camera_config_t> Config::_loadCameras(const libconfig::Setting &root)
{
    std::list<camera_config_t> cameras = {};
    camera_config_t camera;
    unsigned height, width;
    const libconfig::Setting &cameras_cfg = root["cameras"];

    if (!cameras_cfg.isList()){
        throw Config::Exception("cameras must be a list");
    }
    for (int i = 0; i < cameras_cfg.getLength(); i++) {
        const libconfig::Setting &camera_cfg = cameras_cfg[i];
        if (!camera_cfg.exists("resolution") || !camera_cfg.exists("position") || !camera_cfg.exists("rotation") || !camera_cfg.exists("fieldOfView"))
            throw Config::Exception("camera must have resolution, position, rotation and fieldOfView");
        if (!camera_cfg["resolution"].isGroup())
            throw Config::Exception("resolution must be a list of 2 integers");
        if (!camera_cfg["rotation"].isGroup())
            throw Config::Exception("rotation must be a list of 3 doubles");
        if (!camera_cfg["position"].isGroup())
            throw Config::Exception("position must be a list of 3 doubles");
        camera_cfg["resolution"].lookupValue("height", height);
        camera_cfg["resolution"].lookupValue("width", width);
        camera.resolution = {height, width};
        camera.position = _getPoint3D(camera_cfg["position"]);
        camera.rotation = _getVector3D(camera_cfg["rotation"]);
        camera.fov = camera_cfg["fieldOfView"];
        cameras.push_back(camera);
    }
    return cameras;
}

std::list<scene_object_config_t> Config::_loadSceneObjects(const libconfig::Setting &root)
{
    std::list<scene_object_config_t> scene_objects;
    const libconfig::Setting &scene_objects_cfg = root["scene_objects"];
    std::string type;

    if (!scene_objects_cfg.isList())
        throw Config::Exception("scene_objects must be a list");
    if (scene_objects_cfg.getLength() == 0)
        throw Config::Exception("scene_objects must have at least one object");
    for (int i = 0; i < scene_objects_cfg.getLength(); i++) {
        const libconfig::Setting &scene_object_cfg = scene_objects_cfg[i];
        if (!scene_object_cfg.exists("type")) {
            throw Config::Exception("scene_object must have a type");
        }
        if (scene_object_cfg.lookupValue("type", type) == false) {
            throw Config::Exception("type must be a string");
        }
    }
    return scene_objects;
}

Math::Vector3D Config::_getVector3D(const libconfig::Setting &setting)
{
    Math::Vector3D vector3;

    if (!setting.isGroup())
        throw Config::Exception("color must be a list of 3 doubles");
    if (!setting.exists("x") || !setting.exists("y") || !setting.exists("z"))
        throw Config::Exception("color must have x, y and z");
    if (!setting["x"].isNumber() || !setting["y"].isNumber() || !setting["z"].isNumber())
        throw Config::Exception("x, y and z must be floats");
    if (setting.lookupValue("x", vector3.x) == false)
        throw Config::Exception("x must be a float");
    if (setting.lookupValue("y", vector3.y) == false)
        throw Config::Exception("y must be a float");
    if (setting.lookupValue("z", vector3.z) == false)
        throw Config::Exception("z must be a float");
    return vector3;
}

Math::Point3D Config::_getPoint3D(const libconfig::Setting &setting)
{
    Math::Point3D point3;

    if (!setting.isGroup())
        throw Config::Exception("color must be a list of 3 doubles");
    if (!setting.exists("x") || !setting.exists("y") || !setting.exists("z"))
        throw Config::Exception("color must have x, y and z");
    if (!setting["x"].isNumber() || !setting["y"].isNumber() || !setting["z"].isNumber())
        throw Config::Exception("x, y and z must be floats");
    if (setting.lookupValue("x", point3.x) == false)
        throw Config::Exception("x must be a float");
    if (setting.lookupValue("y", point3.y) == false)
        throw Config::Exception("y must be a float");
    if (setting.lookupValue("z", point3.z) == false)
        throw Config::Exception("z must be a float");
    return point3;
}
