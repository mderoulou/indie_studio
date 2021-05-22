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