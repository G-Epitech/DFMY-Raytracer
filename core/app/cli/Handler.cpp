/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.cpp
*/

#include <iostream>
#include "Handler.hpp"
#include "libs/DLLoader/DLLoader.hpp"
#include "common/types/Libraries.hpp"
#include "common/interfaces/IObjectProvider.hpp"

using namespace Raytracer::Core::Cli;


Handler::Handler(Raytracer::Core::App::Arguments &args): _args(args) {}

Handler::~Handler() = default;

int Handler::run() {
    std::cout << "Handler cli running" << std::endl;
    return 0;
}
