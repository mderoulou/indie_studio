/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Vector Fucntions
*/

#include "Vector.hpp"

/*
**  Vector 2 Functions
*/

rl::Vec2::Vec2()
    : ::Vector2{0, 0}
{
}

rl::Vec2::Vec2(float x, float y)
    : ::Vector2{x, y}
{
}

rl::Vec2::Vec2(const Vec2 &vec)
    : ::Vector2{vec.x, vec.y}
{
}

rl::Vec2::Vec2(const ::Vector2 vec)
    : ::Vector2{vec.x, vec.y}
{
}

void rl::Vec2::drawPixel(rl::Color color)
{
    DrawPixelV(*this, color);
}

/*
**  Vector 3 Functions
*/


rl::Vec3::Vec3()
    : ::Vector3{0, 0, 0}
{
}

rl::Vec3::Vec3(float x, float y, float z)
    : ::Vector3{x, y, z}
{
}

/*
**  Vector 3 Functions
*/

rl::Vec4::Vec4()
    : ::Vector4{0, 0, 0, 0}
{
}

rl::Vec4::Vec4(float x1, float y1, float x2, float y2)
    : ::Vector4{x1, y1, x2, y2}
{
}

void rl::Vec4::drawLine(rl::Color color)
{
    DrawLine(x, y, z, w, color);
}