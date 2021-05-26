/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Color funct
*/

#include "Color.hpp"

rl::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
    : ::Color{r, g, b, alpha}
{
}

rl::Color::Color()
    : ::Color{0, 0, 0, 255}
{
}

rl::Color::Color(rl::Vec4 vec)
    : ::Color{static_cast<uint8_t>(vec.x), static_cast<uint8_t>(vec.y), static_cast<uint8_t>(vec.z), static_cast<uint8_t>(vec.w)}
{
}

rl::Color::Color(int hexValue)
{
    ::Color color = GetColor(hexValue);
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
}

int rl::Color::getHexa()
{
    return ColorToInt(*this);
}

rl::Vec4 rl::Color::colorNormalize()
{
    return rl::Vec4(ColorNormalize(*this));
}