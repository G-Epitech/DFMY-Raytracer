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

typedef struct {
    float fov;
    float aspect_ratio;
    float aperture;
    float focus_distance;
} camera_config_t;

typedef struct {
    int caca;
} scene_config_t;

class Config {
    public:
        Config();
        ~Config() = default;

        scene_config_t load(const std::string &path);
};

