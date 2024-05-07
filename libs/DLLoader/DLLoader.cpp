/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

#include <utility>

void DLLoader::_throwError()
{
    std::string error = dlerror();

    throw DLLoaderException(error.empty() ? "Unknown error while loading library" : error);
}

DLLoader::DLLoader(const std::string &filepath, LoadingMode mode)
{
    this->_handle = dlopen(filepath.c_str(), mode);
    if (!this->_handle)
        _throwError();
    dlerror();
}

DLLoader::~DLLoader() {
    if (this->_handle)
        dlclose(this->_handle);
}

std::shared_ptr<DLLoader> DLLoader::open(const std::string &filepath, DLLoader::LoadingMode mode)
{
    return std::make_shared<DLLoader>(filepath, mode);
}

DLLoader::DLLoaderException::DLLoaderException(std::string message) : _message(std::move(message)) {}

const char *DLLoader::DLLoaderException::what() const noexcept
{
    return this->_message.c_str();
}
