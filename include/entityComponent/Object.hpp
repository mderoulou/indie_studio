/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#ifndef INDIE_OBJ_
#define INDIE_OBJ_

#include "rayLib.hpp"

class IObject
{
    public:
        virtual ~IObject() = default;
    private:
};

// 2d object

class Object2D : public IObject
{
public:
    rl::Vec2 pos;
    rl::Color color;
};

class Text : public Object2D
{
public:
    rl::Font font;
    rl::Color color;
};

// 3d object

class Object3D : public IObject
{
public:
    rl::Vec3 pos;
    rl::Color color;
};

class Cube : public Object3D
{
public:
    rl::Vec3 size;
};

#endif