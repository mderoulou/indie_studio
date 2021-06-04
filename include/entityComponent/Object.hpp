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
    rl::Vec2 _pos;
    rl::Color _color;
};

class Text : public Object2D
{
public:
    rl::Font _font;
    rl::Color _color;
};

// 3d object

class Object3D : public IObject
{
public:
    rl::Vec3 _pos;
    rl::Color _color;
};

class Cube : public Object3D
{
public:
    Cube(rl::Vec3 pos, rl::Vec3 size, rl::Color color);

    void handleEvent() override {};
    void move() override {};
    void simulate() override {};
    void render() override;

    rl::Vec3 _size;
};

class Wall : public Cube
{
public:
    Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color);

    void handleEvent() override {};
    void move() override {};
    void simulate() override {};
    void render() override;

    rl::Texture *_atlas;
};

class Player : public Object3D
{
public:
    Player(rl::Vec3 pos, float scale, rl::Color color, std::string pathText); // load Specific texture
    Player(rl::Vec3 pos, float scale, rl::Color color); // steve specific texture
    ~Player();

    void handleEvent() override {};
    void move() override {};
    void simulate() override {};
    void render() override;

    rl::Model *_model;
    rl::Texture *_texture;
    float _scale;
};

#endif