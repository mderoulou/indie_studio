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
        virtual void handleEvent() = 0;
        virtual void move() = 0;
        virtual void simulate() = 0;
        virtual void render() = 0;
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
    Cube(rl::Vec3 pos, rl::Vec3 size, rl::Color color);

    void handleEvent() override {};
    void move() override {};
    void simulate() override {};
    void render() override;

    rl::Vec3 size;
};

class Wall : public Cube
{
public:
    Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color, std::string path, std::string texturePath);

    void handleEvent() override {};
    void move() override {};
    void simulate() override {};
    void render() override;
    rl::Texture *texture;
    rl::Model *model;
};

#endif