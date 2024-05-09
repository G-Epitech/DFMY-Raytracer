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
    if (!_loadPlugins())
        return 84;
    if (_args.scenes.empty()) {
        std::cerr << "No scene file provided." << std::endl;
        return 84;
    }
    if (!tryLoadScene(_args.scenes[0]))
        return 84;
    return _runHandler();
}

int App::_runHandler() {
    Context context = {
        .scene = _scene,
        .pluginsManager = _pluginsManager,
        .args = _args
    };

    if (_args.options.gui) {
        return Gui::Handler(context).run();
    } else {
        return Cli::Handler(context).run();
    }
}

int App::help() {
    std::cout << "USAGE: ./raytracer [options] <scene file>" << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "  Raytracer is a program that generates images using ray tracing." << std::endl;
    std::cout << "  It takes a scene file as input and generates an image based on the scene description." << std::endl;
    std::cout << "  The generated image is saved as a PPM file." << std::endl;
    std::cout << "ARGUMENTS:" << std::endl;
    std::cout << "  <scene file>\t\t\t\tPath to the scene file" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  -g, --gui\t\t\t\tLaunch the graphical user interface" << std::endl;
    std::cout << "  -h, --help\t\t\t\tDisplay this help message" << std::endl;
    std::cout << "  -p, --plugin-path <path = ./plugins>\tSpecify the path to the plugins directory" << std::endl;
    std::cout << "  -f, --format <format = PPM>\t\tSpecify the output image format. Supported formats: PPM, PNG, JPEG, BMP" << std::endl;
    std::cout << "  -t, --threads <count = 8>\t\tSpecify the number of threads to use." << std::endl;
    std::cout << "AUTHORS: " << std::endl;
    std::cout << "  Dragos Suceveanu, "
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
        {"plugin-path", required_argument, nullptr, 'p'},
        {"threads", required_argument, nullptr, 't'},
        { "format", required_argument, nullptr, 'f' },
        {nullptr, 0, nullptr, 0}
    };
    int parsedChar;

    do {
        parsedChar = getopt_long(argc, argv, "ghp:t:f:", long_options, nullptr);
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
            case 't':
                if (!_readUL(optarg, _args.options.threadsCount)) {
                    std::cerr << "Invalid threads count: '" << optarg << "'." << std::endl;
                    return false;
                }
                if (_args.options.threadsCount == 0 || _args.options.threadsCount > 64) {
                    std::cerr << "Threads count must be in range [1, 64]." << std::endl;
                    return false;
                }
                if (_args.options.threadsCount % 2 != 0)
                    _args.options.threadsCount += 1;
                break;
            case 'f':
                if (!_readOutputFormat(optarg, _args.options.outputFormat)) {
                    std::cerr << "Invalid output format: '" << optarg << "'." << std::endl;
                    return false;
                }
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

bool App::tryLoadScene(const string &scenePath) {
    try {
        auto config = Config::loadFromFile(scenePath);
        auto scene = config.toScene(_pluginsManager);

        _scene = std::move(scene);
        return true;
    } catch (const ConfigException &e) {
        std::cerr << "An error occurred while loading the scene file. " << e.what() << "." << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while creating the scene. " << e.what() << std::endl;
        return false;
    }
}

bool App::_readUL(const std::string& arg, size_t &value) {
    try {
        if (arg[0] == '-')
            return false;
        value = std::stoul(arg);
        return true;
    } catch (...) {
        return false;
    }
}

bool App::_readOutputFormat(const std::string &arg, std::string &outputFormat) {
    std::string copy = arg;
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    if (copy == "ppm" || copy == "png" || copy == "jpeg" || copy == "bmp") {
        outputFormat = copy;
        return true;
    }
    return false;
}
