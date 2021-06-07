/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Vector Class
*/

#ifndef RL_VECTOR_
#define RL_VECTOR_

#include "rayLib.hpp"

namespace rl {

class Color;

class Vec2 : public ::Vector2
{
    public:
        Vec2();
        Vec2(float x, float y);
        Vec2(const Vec2 &vec);
        Vec2(const ::Vector2 vec);
        ~Vec2() {};

        void drawPixel(rl::Color color);
    private:
};

class Vec3 : public ::Vector3
{
    public:
        Vec3();
        Vec3(float x, float y, float z);
        ~Vec3() {};

        void drawCube(rl::Vec3 size, rl::Color color);
        void drawCubeWires(rl::Vec3 size, rl::Color color);
    private:
};

class Vec4 : public ::Vector4
{
    public:
        Vec4();
        Vec4(float x1, float y1, float x2, float y2);
        Vec4(const Vec4 &vec);
        Vec4(const ::Vector4 &vec);
        ~Vec4() {};

        void drawLine(rl::Color color);
    private:
};

}

#endif
