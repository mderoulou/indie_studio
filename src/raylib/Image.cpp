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

rl::Image::Image()
{
    _img = GetScreenData();
}

rl::Image::~Image()
{
    UnloadImage(_img);
}

void rl::Image::clearBackground(rl::Color color)
{
    ImageClearBackground(&_img, color);
}

void rl::Image::drawPixel(int x, int y, rl::Color color)
{
    ImageDrawPixel(&_img, x, y, color);
}

void rl::Image::drawLine(rl::Vec4 vec, rl::Color color)
{
    ImageDrawLine(&_img, vec.x, vec.y, vec.z, vec.w, color);
}

void rl::Image::drawRect(rl::Rectangle rect, rl::Color color)
{
    ImageDrawRectangle(&_img, rect.x, rect.y, rect.width, rect.height, color);
}

void rl::Image::drawCircle(int x, int y, int raduis, rl::Color color)
{
    ImageDrawCircle(&_img, x, y, raduis, color);
}

void rl::Image::crop(rl::Rectangle rect)
{
    ImageCrop(&_img, rect);
}

void rl::Image::resize(int width, int height)
{
    ImageResize(&_img, width, height);
}

void rl::Image::setGrayscale()
{
    ImageColorGrayscale(&_img);
}

void rl::Image::flipV()
{
    ImageFlipVertical(&_img);
}

void rl::Image::flipH()
{
    ImageFlipHorizontal(&_img);
}