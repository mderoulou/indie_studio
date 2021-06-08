/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Rectangle Class
*/

#ifndef RL_RECTANLE_
#define RL_RECTANLE_

#include "rayLib.hpp"

namespace rl {

class Color;

class Rectangle : public ::Rectangle
{
    public:
        Rectangle(float x, float y, float width, float height);
        Rectangle(const Rectangle &rect);
        ~Rectangle() {};

        void draw(rl::Color color);
        void drawLine(rl::Color color);

        const Rectangle getCollisionRec(rl::Rectangle rect);
        bool checkCollision(Vector2 pos);

    private:
};

}

#endif