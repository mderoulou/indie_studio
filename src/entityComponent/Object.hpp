/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#ifndef INDIE_OBJ_
#define INDIE_OBJ_

#include "../raylib/rayLib.hpp"


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

// 2d object

class Object2D : public IObject
{
public:
    void handleEvent() override {};
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override {};

    rl::Vec2 _pos;
    rl::Color _color;
};

class Text : public Object2D
{
public:
    rl::Font _font;
    rl::Color _color;
};

class Btn : public Object2D
{
public:
    Btn(const rl::Vec2 &pos, const rl::Rectangle &src, const std::string &textureFile, const std::string &soundFile, const rl::Color &color = rl::Color(0xFFFFFF));
    
    short _btnState;
    bool _clicked;
    rl::Rectangle _src;
    rl::Rectangle _bound;
    rl::Vec2 _pos;
    rl::Color _color;
    rl::Sound _sound;
    rl::Texture _texture;

    void handleEvent() override;
    void render() override;
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
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;

    rl::Vec3 _size;
    bool _isBreakable;
};

class Wall : public Cube
{
public:
    Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color, bool isWall);

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;

    rl::Texture *_texture;
    rl::Model *_model;
};

class Box : public Cube
{
public:
    Box(rl::Vec3 pos, rl::Vec3 size, rl::Color color);

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;

    rl::Texture *_txt;
    rl::Model *_model;
};

class Player : public Object3D
{
public:
    Player(rl::Vec3 pos, float scale, rl::Color color, std::string pathText); // load Specific texture
    Player(rl::Vec3 pos, float scale, rl::Color color); // steve specific texture
    ~Player();

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;

    rl::Model *_model;
    rl::Texture *_texture;
    rl::ModelAnimation *_anim;
    float _scale;
    float _rotation;
    int _frame;
};

#endif