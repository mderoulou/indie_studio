/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Image Functions
*/

#include "Image.hpp"

rl::Image::Image(const std::string filename)
{
    _img = LoadImage(filename.c_str());
}

rl::Image::Image(const std::string filename, int width, int height, int format, int headerSize)
{
    _img = LoadImageRaw(filename.c_str(), width, height, format, headerSize);
}

rl::Image::Image(const Image &img)
{
    _img = ImageCopy(img.getImg());
}

rl::Image::~Image()
{
    UnloadImage(_img);
}