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
    libconfig::Config cfg;
    scene_config_t scene_config;
    scene_config.caca = 42;
    std::cout << "Loading config from " << path << std::endl;
    int value;
    std::string str;
    float fvalue;
    bool bvalue;

    cfg.readFile(path.c_str());
    cfg.lookupValue("integerValue", value);
    cfg.lookupValue("stringValue", str);
    cfg.lookupValue("floatValue", fvalue);
    cfg.lookupValue("boolValue", bvalue);
    std::cout << "integerValue: " << value << std::endl;
    std::cout << "stringValue: " << str << std::endl;
    std::cout << "floatValue: " << fvalue << std::endl;
    std::cout << "boolValue: " << bvalue << std::endl;
    return scene_config;
}
