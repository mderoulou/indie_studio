/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#ifndef INDIE_OBJ_
#define INDIE_OBJ_

#include "ByteObject.hpp"
#include "../raylib/rayLib.hpp"
#include <vector>
#include <string.h>

class ComponentManager;
class Bomberman;
class Bomb;

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
        virtual ~AObject();
        virtual void handleEvent() = 0;
        virtual void move(rl::Vec3 newPos)
        {
            _pos +=  newPos;
            _boundingBox._bd.min = rl::Vec3(_boundingBox._bd.min) + newPos;
            _boundingBox._bd.max = rl::Vec3(_boundingBox._bd.max) + newPos;
        }
        
        virtual std::shared_ptr<ByteObject> dump(){
            auto obj = std::make_shared<ByteObject>();
            *obj << ByteObject::DEFAULT;
            return obj;
        }

        virtual void load(std::shared_ptr<ByteObject> obj) {
        }

        virtual void simulate() = 0;
        virtual bool explode(Bomb *bomb);
        virtual void render(rl::Camera3d *cam) = 0;
        virtual float &operator[](int i) {return _pos[i];}

        rl::Vec3 _pos;
        int _scene = 0;
        bool _toRemove = false;
        bool _isSolid = false;
        rl::BoundingBox _boundingBox = {rl::Vec3(0, 0, 0), rl::Vec3(0, 0, 0)};
        ComponentManager *_manager;
        enum dimension {
            DIMENSION2,
            DIMENSION3,
        };

        dimension _dimension;

    private:
};

class Object2D : public AObject
{
public:
    void handleEvent() override {};
    void move(rl::Vec3 newPos) override { (void)newPos; };
    void simulate() override {};
    void render(rl::Camera3d *cam) override { (void)cam; };

    rl::Color _color;
};

class Object3D : public AObject
{
public:
    rl::Color _color = {255, 255, 255, 255};
};


#include "object/Btn.hpp"
#include "object/Cube.hpp"
#include "object/Input.hpp"
#include "object/Slider.hpp"
#include "object/List.hpp"
#include "object/MusicManager.hpp"
#include "object/EscManager.hpp"
#include "object/Player.hpp"
#include "object/Text.hpp"
#include "object/Wall.hpp"
#include "object/Box.hpp"
#include "object/Preview.hpp"
#include "object/GameOpt.hpp"
#include "object/Bomb.hpp"
#include "object/Skybox.hpp"
#include "object/Floor.hpp"

#endif