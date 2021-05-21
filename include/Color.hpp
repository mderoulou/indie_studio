/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Color Class
*/

#ifndef RL_COLOR_
#define RL_COLOR_

#include "rayLib.hpp"

namespace rl {
    
class Color : public ::Color
{
    public:
        Color(int r, int g, int b, int alpha) : ::Color{r, g, b, alpha} {};
        ~Color() {};
};

}


#endif