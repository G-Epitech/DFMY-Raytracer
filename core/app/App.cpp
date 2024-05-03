/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** App.cpp
*/

#include <iostream>
#include "App.hpp"

using namespace Raytracer::Core;

int App::run(int argc, char **argv)
{
    return help();
}

int App::help() {
    std::cout << "USAGE: ./raytracer [options] <scene file>" << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "  Raytracer is a program that generates images using ray tracing." << std::endl;
    std::cout << "  It takes a scene file as input and generates an image based on the scene description." << std::endl;
    std::cout << "  The generated image is saved as a PPM file." << std::endl;
    std::cout << "ARGUMENTS:" << std::endl;
    std::cout << "  <scene file>\t\tPath to the scene file" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  -g, --gui\t\tLaunch the graphical user interface" << std::endl;
    std::cout << "  -h, --help\t\tDisplay this help message" << std::endl << std::endl;
    std::cout << "AUTHORS: "
                << "Dragos Suceveanu, "
                << "Flavien Chenu, "
                << "Matheo Coquet & "
                << "Yann Masson"
    << std::endl;
    return 0;
}
