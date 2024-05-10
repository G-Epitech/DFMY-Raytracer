/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Image.cpp
*/

#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "PixelArray.hpp"

using namespace Raytracer::Core::Graphics;

Image::Image(size_t width, size_t height, PixelArray &array): width(width), height(height)
{
    _image.create(width, height, array.get());
}

bool Image::saveTo(const std::string &path) const
{
    auto extension = path.substr(path.find_last_of('.') + 1);

    if (extension == path || extension == "ppm")
        return _saveAsPpm(path);
    else
        return _image.saveToFile(path);
}

bool Image::_saveAsPpm(const std::string &path) const {
    auto pixels =  _image.getPixelsPtr();
    std::ofstream file;

    if (!pixels)
        return false;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open())
        return false;
    file << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i = 0; i < width * height * 4; i += 4) {
        file << pixels[i] << pixels[i + 1] << pixels[i + 2];
    }
    file.close();
    return true;
}

Image::~Image() = default;
