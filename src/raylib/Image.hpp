/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Image Class
*/

#ifndef RL_IMAGE_
#define RL_IMAGE_

#include "raylib.h"
#include "Color.hpp"
#include "Vector.hpp"
#include "Rectangle.hpp"
#include <string>


namespace rl {

class Image
{
    public:
    Image(const std::string fileName);
    Image(const std::string fileName, int width, int height, int format, int headerSize);
    Image(const Image &img);
    Image(); // take a screenshot
    ~Image();

    ::Image getImg() const { return _img; };

    void clearBackground(rl::Color color);
    void drawPixel(int x, int y, rl::Color color);
    void drawLine(rl::Vec4 vec, rl::Color color);
    void drawRect(rl::Rectangle rect, rl::Color color);
    void drawCircle(int x, int y, int radius, rl::Color color);
    
    void crop(rl::Rectangle rect);
    void resize(int width, int height);
    void setGrayscale();
    void flipV();
    void flipH();

    private:
    ::Image _img;
};

}

#endif