/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

void DLLoader::_throwError()
{
    std::string error = dlerror();

    throw DLLoaderExeption(error.empty() ? "Unknown error while loading library" : error);
}

DLLoader::DLLoader(const std::string &filepath, LoadingMode mode)
{
    this->_handle = dlopen(filepath.c_str(), mode);
    if (!this->_handle)
        this->_throwError();
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

DLLoader::DLLoaderExeption::DLLoaderExeption(const std::string &message) : _message(message) {}

const char *DLLoader::DLLoaderExeption::what() const noexcept
{
    return this->_message.c_str();
}
