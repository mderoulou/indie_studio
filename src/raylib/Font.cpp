/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Font Functions
*/

#include "Font.hpp"

rl::Font::Font()
{
    _font = GetFontDefault();
}

rl::Font::Font(const std::string filename)
{
    _font = LoadFont(filename.c_str());
}

rl::Font::~Font()
{
    UnloadFont(_font);
}

void rl::Font::drawFPS(int posX, int posY)
{
    DrawFPS(posX, posY);
}

void rl::Font::drawText(std::string text, int posX, int posY, int fontSize, rl::Color color)
{
    DrawText(text.c_str(), posX, posY, fontSize, color);
}

void rl::Font::drawTextEx(std::string text, rl::Vec2 pos, float fontSize, float spacing, rl::Color color)
{
    DrawTextEx(_font, text.c_str(), pos, fontSize, spacing, color);
}

rl::Vec2 rl::Font::MesasureText(std::string text, float fontSize, float spacing)
{
    return rl::Vec2(MeasureTextEx(_font, text.c_str(), fontSize, spacing));
}