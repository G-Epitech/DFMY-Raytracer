/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"

#include <utility>

using namespace Raytracer::Core::Rendering;

Scene::Scene(std::string name): name(std::move(name)) {}
