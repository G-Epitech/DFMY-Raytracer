/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Image.cpp
*/

#include "Image.hpp"
#include "PixelArray.hpp"

using namespace Raytracer::Core::Graphics;

Image::Image(size_t width, size_t height, PixelArray &array): width(width), height(height)
{
    _image.create(width, height, array.get());
}

bool Image::saveTo(const std::string &path) const
{
    return _image.saveToFile(path);
}


