/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** Config
*/

#pragma once

#include <libconfig.h++>
#include <iostream>
#include <list>
#include <tuple>

typedef struct {
    std::pair<int, int> resolution;
    std::tuple<double, double, double> position;
    std::tuple<double, double, double> rotation;
    float fov;
} camera_config_t;

typedef struct {
    std::list<camera_config_t> cameras;
} scene_config_t;

class Config {
    public:
        Config();
        ~Config() = default;

        scene_config_t load(const std::string &path);

    private:
        std::list<camera_config_t> _loadCameras(const libconfig::Setting &root);

        std::tuple<double, double, double> _get3DPoint(const libconfig::Setting &setting);

        libconfig::Config _cfg;
};

