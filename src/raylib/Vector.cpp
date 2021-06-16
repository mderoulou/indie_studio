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

void rl::Vec3::drawCube(rl::Vec3 size, rl::Color color)
{ 
    DrawCubeV(rl::Vec3(this->x, this->y, this->z), size, color);
}

void rl::Vec3::drawCubeWires(rl::Vec3 size, rl::Color color)
{
    DrawCubeWiresV(rl::Vec3(this->x, this->y, this->z), size, color);
}


/*
**  Vector 4 Functions
*/

rl::Vec4::Vec4()
    : ::Vector4{0, 0, 0, 0}
{
}

rl::Vec4::Vec4(float x1, float y1, float x2, float y2)
    : ::Vector4{x1, y1, x2, y2}
{
}

rl::Vec4::Vec4(const rl::Vec4 &vec)
    : ::Vector4{vec.x, vec.y, vec.z, vec.w}
{
}

rl::Vec4::Vec4(const ::Vector4 &vec)
    : ::Vector4{vec.x, vec.y, vec.z, vec.w}
{
}

void rl::Vec4::drawLine(rl::Color color)
{
    DrawLine(x, y, z, w, color);
}