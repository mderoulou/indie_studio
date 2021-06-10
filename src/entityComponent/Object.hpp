/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#ifndef INDIE_OBJ_
#define INDIE_OBJ_

#include "../raylib/rayLib.hpp"

class ComponentManager;
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

class AObject : public IObject
{
    public:
        virtual ~AObject() = default;
        virtual void handleEvent() = 0;
        virtual void move(rl::Vec3 newPos) {
            _pos +=  newPos;
            _boundingBox._bd.min = rl::Vec3(_boundingBox._bd.min) + newPos;
            _boundingBox._bd.max = rl::Vec3(_boundingBox._bd.max) + newPos;
        }
        virtual void simulate() = 0;
        virtual void render(rl::Camera3d *cam) = 0;
        virtual float &operator[](int i) {
            return _pos[i];
        }

        rl::Vec3 _pos;
        bool _isSolid = false;
        rl::BoundingBox _boundingBox = {rl::Vec3(0, 0, 0), rl::Vec3(0, 0, 0)};
        ComponentManager *_manager;
    private:
};

class Object2D : public AObject
{
public:
    void handleEvent() override {};
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override {};

    rl::Color _color;
    int _scene = 0;
};

class Object3D : public AObject
{
public:
    rl::Color _color;
    int _scene = 0;
};


#include "object/Btn.hpp"
#include "object/Cube.hpp"
#include "object/Input.hpp"
#include "object/List.hpp"
#include "object/Player.hpp"
#include "object/Text.hpp"
#include "object/Wall.hpp"
#include "object/Background.hpp"
#include "object/Box.hpp"

#endif