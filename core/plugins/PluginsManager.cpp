/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjectFactory.cpp
*/

#include "PluginsManager.hpp"
#include "types/Libraries.hpp"

#include <utility>
#include <filesystem>

using namespace Raytracer::Core;

PluginsManager::Exception::Exception(std::string message): _message(std::move(message)) {}

const char *PluginsManager::Exception::what() const noexcept {
    return _message.c_str();
}

PluginsManager::PluginsManager() = default;

PluginsManager::~PluginsManager() {
    providers.clear();
}

void PluginsManager::load(const std::string& pluginsDir) {
    if (!std::filesystem::exists(pluginsDir))
        throw InvalidPathException(pluginsDir, InvalidPathException::Reason::NOT_FOUND);
    if (!std::filesystem::is_directory(pluginsDir))
        throw InvalidPathException(pluginsDir, InvalidPathException::Reason::NOT_DIRECTORY);
    auto dir = std::filesystem::directory_iterator(pluginsDir);
    for (const auto &entry : dir) {
        if (entry.is_regular_file())
            _loadPlugin(entry.path());
    }
}

void PluginsManager::_loadPlugin(const std::string &filepath) {
    std::string getterName = STRINGIFY(OBJECT_PROVIDER_GETTER_NAME);

    try {
        auto loader = DLLoader::open(filepath);
        auto getter = loader->loadSymbol<Common::ObjectProviderGetter>(getterName);
        IObjectProvider::Ptr provider(getter());

        _registerPlugin(std::move(provider));
        _loaders.push_back(loader);
    } catch (const DLLoader::DLLoaderException &e) {
        throw Exception(e.what());
    }
}

void PluginsManager::_registerPlugin(IObjectProvider::Ptr provider) {
    auto manifest = provider->getManifest();
    auto concurrent = providers.find(manifest.name);

    if (concurrent != providers.end())
        throw Exception("Duplicated plugin with name '" + manifest.name + "'");
    providers[manifest.name] = std::move(provider);
}

PluginsManager::InvalidPathException::InvalidPathException(const std::string &path,
    PluginsManager::InvalidPathException::Reason reason): Exception("Invalid path: " + path), _path(path), _reason(reason) {}

const char *PluginsManager::InvalidPathException::path() const noexcept {
    return _path.c_str();
}

PluginsManager::InvalidPathException::Reason PluginsManager::InvalidPathException::reason() const noexcept {
    return _reason;
}

