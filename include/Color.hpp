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
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
        Color();
        ~Color() {};

};

}


#endif