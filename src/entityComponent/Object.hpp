/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#ifndef INDIE_OBJ_
#define INDIE_OBJ_

#include "../raylib/rayLib.hpp"

class Bomberman;

class IObject
{
    public:
        virtual ~IObject() = default;
        virtual void handleEvent() = 0;
        virtual void move(rl::Vec3 newPos) = 0;
        virtual void simulate() = 0;
        virtual void render(rl::Camera3d *cam) = 0;
    private:
};

class Object2D : public IObject
{
public:
    void handleEvent() override {};
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override {};

    rl::Vec2 _pos;
    rl::Color _color;
    int _scene = 0;
};

class Object3D : public IObject
{
public:
    rl::Vec3 _pos;
    rl::Color _color;
    int _scene = 0;
};


#include "object/Box.hpp"
#include "object/Btn.hpp"
#include "object/Cube.hpp"
#include "object/Input.hpp"
#include "object/Player.hpp"
#include "object/Text.hpp"
#include "object/Wall.hpp"

#endif