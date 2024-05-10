/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.cpp
*/

#include <iostream>
#include "Handler.hpp"

using namespace Raytracer::Core::Gui;

Handler::Handler(Raytracer::Core::App::Context &context): _appContext(context) {}

Handler::~Handler() = default;

int Handler::run() {
    std::cout << "Handler gui running" << std::endl;
    return 0;
}
