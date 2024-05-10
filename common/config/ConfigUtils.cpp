/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ConfigUtils
*/

#include "ConfigUtils.hpp"


std::tuple<float, float, float> ConfigUtils::parseTuple3f(const std::string& prop,
    const libconfig::Setting &setting, const std::vector<std::string>& keys)
{
    std::tuple<float, float, float> tuple;
    settingHasValidKeys(prop, setting, keys);
    lookupValueWrapper(keys[0], setting, std::get<0>(tuple));
    lookupValueWrapper(keys[1], setting, std::get<1>(tuple));
    lookupValueWrapper(keys[2], setting, std::get<2>(tuple));
    return tuple;
}

Math::Vector3D ConfigUtils::parseVector3D(const std::string& propName, const libconfig::Setting &setting)
{
    Math::Vector3D vector3;
    std::tuple<float, float, float> tuple;

    if (!setting.isGroup())
        throw std::runtime_error(propName + " must be a group of 3 floats {x, y, z}");
    tuple = parseTuple3f(propName, setting, {"x", "y", "z"});
    vector3.x = std::get<0>(tuple);
    vector3.y = std::get<1>(tuple);
    vector3.z = std::get<2>(tuple);
    return vector3;
}

Math::Point3D ConfigUtils::parsePoint3D(const std::string& propName, const libconfig::Setting &setting)
{
    Math::Point3D point3;
    std::tuple<float, float, float> tuple;

    if (!setting.isGroup())
        throw std::runtime_error(propName + " must be a list of 3 floats");
    tuple = parseTuple3f(propName, setting, {"x", "y", "z"});
    point3.x = std::get<0>(tuple);
    point3.y = std::get<1>(tuple);
    point3.z = std::get<2>(tuple);
    return point3;
}

Raytracer::Common::Graphics::Color ConfigUtils::parseColor(const libconfig::Setting &setting)
{
    Raytracer::Common::Graphics::Color color;
    std::tuple<int, int, int, int> icolor;

    if (!setting.isGroup())
        throw std::runtime_error("color must be a group of 4 integers");
    settingHasValidKeys("color", setting, {"r", "g", "b", "a"});
    lookupValueWrapper("r", setting, std::get<0>(icolor));
    lookupValueWrapper("g", setting, std::get<1>(icolor));
    lookupValueWrapper("b", setting, std::get<2>(icolor));
    lookupValueWrapper("a", setting, std::get<3>(icolor));
    return Raytracer::Common::Graphics::Color::fromRGB(
        std::get<0>(icolor),
        std::get<1>(icolor),
        std::get<2>(icolor),
        std::get<3>(icolor)
    );
}

void ConfigUtils::settingHasValidKeys(const std::string& prop, const libconfig::Setting &setting,
    const std::vector<std::string> &keys)
{
    bool has_all_keys = true;
    std::string error_msg = prop + " must have ";

    for (int i = 0; i < keys.size(); i++){
        if (!setting.exists(keys[i])) {
            has_all_keys = false;
        }
        if (i == keys.size() - 1) {
            error_msg += "\"" + keys[i] + "\"";
        } else {
            error_msg += "\"" + keys[i] + "\"" + ", ";
        }
    }
    if (!has_all_keys) {
        throw std::runtime_error(error_msg + " as keys");
    }
}
