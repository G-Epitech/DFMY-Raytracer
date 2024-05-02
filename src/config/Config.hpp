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
    std::tuple<double, double, double> position;
    float radius;
    std::tuple<double, double, double> color;
} sphere_config_t;

typedef union {
    sphere_config_t sphere;
} scene_object_config_t;

typedef struct {
    std::list<camera_config_t> cameras;
    std::list<scene_object_config_t> scene_objects;
} scene_config_t;

class Config {
    public:
        Config();
        ~Config() = default;

        scene_config_t load(const std::string &path);

        class Exception : public std::exception {
            public:
                explicit Exception(std::string const &message)
                    : _message(message) {}

                const char *what() const noexcept override {
                    return _message.c_str();
                }
                const std::string &getMessage() const {
                    return _message;
                }
            private:
                std::string _message;
        };
    private:
        std::list<camera_config_t> _loadCameras(const libconfig::Setting &root);
        std::list<scene_object_config_t> _loadSceneObjects(const libconfig::Setting &root);

        std::tuple<double, double, double> _get3DPoint(const libconfig::Setting &setting);
};

