/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Font Class
*/

#ifndef RL_FONT_
#define RL_FONT_

#include <string>
#include "raylib.h"
#include "Color.hpp"
#include "Vector.hpp"

namespace rl {

class Font
{
    public:
        Font(); // to get the default font
        Font(const std::string fileName);
        ~Font();

        void drawFPS(int posX, int posY);
        void drawText(std::string text, int posX, int posY, int fontSize, rl::Color color); // using the default font
        void drawTextEx(std::string text, rl::Vec2 pos, float fontSize, float spacing, rl::Color color);

        rl::Vec2 MesasureText(std::string text, float fontSize, float spacing);
    private:
        ::Font _font;
};

}

#endif
