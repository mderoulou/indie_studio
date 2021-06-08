/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Rectangle Functions
*/

#include "Rectangle.hpp"

rl::Rectangle::Rectangle(float x = 0, float y = 0, float width = 0, float height = 0)
    : ::Rectangle{x, y, width, height}
{
}

rl::Rectangle::Rectangle(const rl::Rectangle &rect)
    : ::Rectangle{rect.x, rect.y, rect.width, rect.height}
{
}

void rl::Rectangle::draw(rl::Color color)
{
    DrawRectangle(x, y, width, height, color);
}

void rl::Rectangle::drawLine(rl::Color color)
{
    DrawRectangleLines(x, y, width, height, color);
}

const rl::Rectangle rl::Rectangle::getCollisionRec(rl::Rectangle rect)
{
    ::Rectangle newRect = GetCollisionRec(*this, rect);
    return rl::Rectangle(newRect.x, newRect.y, newRect.width, newRect.height);
}

bool rl::Rectangle::checkCollision(Vector2 pos)
{
    return CheckCollisionPointRec(pos, ::Rectangle{x, y, width, height});
}