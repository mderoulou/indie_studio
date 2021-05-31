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

class Object : public IObject
{
    public:
        rl::Vec3 pos;
        rl::Color color;
};

class Line : public Object
{
    public:
        rl::Vec3 posSecond;
};

class Circle : public Object
{
    public:
        float r;
};

class Sphere : public Circle
{
    public:
};

class Square : public Object
{
    public:
        rl::Vec2 size;
};

class Cube : public Object
{
    public:
        rl::Vec3 size;
};

class Npc : public Object
{
    public:
        rl::Model model;
        rl::ModelAnimation anims;
};

#endif