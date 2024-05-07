/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** App.cpp
*/

#include <iostream>
#include <getopt.h>
#include <filesystem>
#include "App.hpp"
#include "gui/Handler.hpp"
#include "cli/Handler.hpp"
#include "config/Config.hpp"
#include "plugins/PluginsManager.hpp"

using namespace Raytracer::Core;

int App::run(int argc, char **argv)
{
    if (!_readArgs(argc, argv))
        return 84;
    if (_args.options.help)
        return help();
    Config configLoader(_args.scenes[0]);
    if (!_loadPlugins())
        return 84;
    configLoader.load();
    configLoader.toScene(_pluginsManager);

    return _runHandler();
}

int App::_runHandler() {
    if (_args.options.gui) {
        return Gui::Handler(_args).run();
    } else {
        return Cli::Handler(_args).run();
    }
}

int App::help() {
    std::cout << "USAGE: ./raytracer [options] <scene file>" << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "  Raytracer is a program that generates images using ray tracing." << std::endl;
    std::cout << "  It takes a scene file as input and generates an image based on the scene description." << std::endl;
    std::cout << "  The generated image is saved as a PPM file." << std::endl;
    std::cout << "ARGUMENTS:" << std::endl;
    std::cout << "  <scene file>\t\t\tPath to the scene file" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  -g, --gui\t\t\tLaunch the graphical user interface" << std::endl;
    std::cout << "  -h, --help\t\t\tDisplay this help message" << std::endl;
    std::cout << "  -p, --plugin-path <path>\tSpecify the path to the plugins directory" << std::endl;
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
        { "plugin-path", required_argument, nullptr, 'p'},
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
            case 'p':
                _args.options.pluginsPath = optarg;
                break;
            default:
                return false;
        }
    } while (parsedChar != -1);
    return true;
}

bool App::_loadPlugins() {
    if (!std::filesystem::exists(_args.options.pluginsPath)) {
        std::cerr << "Invalid plugins path: '" << _args.options.pluginsPath << "'." << std::endl;
        return false;
    }
    try {
        _pluginsManager.load(_args.options.pluginsPath);
        return true;
    } catch (const PluginsManager::Exception &e) {
        std::cerr << "An error occurred while loading plugins. " << e.what() << std::endl;
        return false;
    }
}
