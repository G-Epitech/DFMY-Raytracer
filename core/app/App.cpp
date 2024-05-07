/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** App.cpp
*/

#include <iostream>
#include <getopt.h>
#include "App.hpp"

#include "gui/Handler.hpp"
#include "cli/Handler.hpp"

using namespace Raytracer::Core;

int App::run(int argc, char **argv)
{
    Gui::Handler guiHandler(_args);
    Cli::Handler cliHandler(_args);

    if (!_readArgs(argc, argv))
        return 84;
    if (_args.options.help)
        return help();
    return _args.options.gui ? guiHandler.run() : cliHandler.run();
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

bool App::_readArgs(int argc, char **argv) {
    if (!_readOptions(argc, argv))
        return false;
    for (int i = optind; i < argc; i++) {
        _args.scenes.emplace_back(argv[i]);
    }
    return true;
}

bool App::_readOptions(int argc, char **argv) {
    static struct option long_options[] = {
        {"gui", no_argument, nullptr, 'g'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0}
    };
    int parsedChar;

    do {
        parsedChar = getopt_long(argc, argv, "gh", long_options, nullptr);
        switch (parsedChar) {
            case -1:
                break;
            case 'g':
                _args.options.gui = true;
                break;
            case 'h':
                _args.options.help = true;
                return true;
            default:
                return false;
        }
    } while (parsedChar != -1);
    return true;
}
