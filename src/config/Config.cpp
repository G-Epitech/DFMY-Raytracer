/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** Config
*/

#include "Config.hpp"

Config::Config()
    : _cfg()
{
}

scene_config_t Config::load(const std::string &path)
{
    scene_config_t scene_config;

    try {
        _cfg.readFile(path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        throw std::runtime_error("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        throw std::runtime_error("Parse error at " + std::to_string(pex.getLine()) + ": " + pex.getError());
    }
    const libconfig::Setting &root = _cfg.getRoot();
    scene_config.cameras = _loadCameras(root);
    return scene_config;
}

std::list<camera_config_t> Config::_loadCameras(const libconfig::Setting &root)
{
    std::list<camera_config_t> cameras = {};
    camera_config_t camera;
    int height, width;
    std::cout << "Config loaded from "  << std::endl;
    const libconfig::Setting &cameras_cfg = root["cameras"];


    if (!cameras_cfg.isList())
        throw std::runtime_error("cameras must be a list");

    for (int i = 0; i < cameras_cfg.getLength(); i++) {
        const libconfig::Setting &camera_cfg = cameras_cfg[i];
        if (!camera_cfg.exists("resolution") || !camera_cfg.exists("position") || !camera_cfg.exists("rotation") || !camera_cfg.exists("fieldOfView"))
            throw std::runtime_error("camera must have resolution, position, rotation and fieldOfView");
        if (!camera_cfg["resolution"].isGroup())
            throw std::runtime_error("resolution must be a list of 2 integers");
        if (!camera_cfg["rotation"].isGroup())
            throw std::runtime_error("rotation must be a list of 3 doubles");
        if (!camera_cfg["position"].isGroup())
            throw std::runtime_error("position must be a list of 3 doubles");
        camera_cfg["resolution"].lookupValue("height", height);
        camera_cfg["resolution"].lookupValue("width", width);
        camera.resolution = {height, width};
        camera.position = _get3DPoint(camera_cfg["position"]);
        camera.rotation = _get3DPoint(camera_cfg["rotation"]);
        camera.fov = camera_cfg["fieldOfView"];
        cameras.push_back(camera);
    }
    return cameras;
}

std::tuple<double, double, double> Config::_get3DPoint(const libconfig::Setting &setting)
{
    double x, y, z;

    if (!setting.isGroup())
        throw std::runtime_error("point must be a list of 3 doubles");
    if (!setting.exists("x") || !setting.exists("y") || !setting.exists("z"))
        throw std::runtime_error("point must have x, y and z");
    if (!setting["x"].isNumber() || !setting["y"].isNumber() || !setting["z"].isNumber())
        throw std::runtime_error("x, y and z must be doubles");
    if (setting.lookupValue("x", x) == false)
        throw std::runtime_error("x must be a double");
    if (setting.lookupValue("y", y) == false)
        throw std::runtime_error("y must be a double");
    if (setting.lookupValue("z", z) == false)
        throw std::runtime_error("z must be a double");
    return {x, y, z};
}
