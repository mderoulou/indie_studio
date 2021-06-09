/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Player Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

Player::Player(rl::Vec3 pos, float scale, rl::Color color, std::string pathText, int scene)
{
    int count = 40;
    _scene = scene;
    _color = color;
    _scale = scale;
    _rotation = 0;
    _texture = new rl::Texture(pathText);
    this->loadAnims();
}

Player::Player(rl::Vec3 pos, float scale, rl::Color color, int scene)
{
    _pos = rl::Vec3(pos);
    _color = rl::Color(color);
    _rotation = 180;
    _scale = scale;
    _texture = new rl::Texture("../assets/steve-obj/player-name/skin.png");
    _frame = 0;
    _scene = scene;
    this->loadAnims();
}

Player::~Player()
{
    delete _texture;
}

void Player::loadAnims()
{
    int count = 41;
    std::ostringstream objPath("");

    for (int i = 1; i < count; i++) {
        if (i < 10)
            objPath << "../assets/steve-obj/anims/steve_0" << i << ".glb";
        else
            objPath << "../assets/steve-obj/anims/steve_" << i << ".glb";
        std::cout << objPath.str().c_str() << std::endl;
        _models.push_back(new rl::Model(objPath.str().c_str()));
        objPath.str("");
        objPath.clear();
    }
    for (auto model : _models)
        model->setMaterialTexture(0, _texture);
}

void Player::render(rl::Camera3d *cam)
{
    cam->beginMode();

    _models[_frame]->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
    cam->endMode();
}

void Player::move(rl::Vec3 newPos)
{
    _pos.x += newPos.x;
    _pos.y += newPos.y;
    _pos.z += newPos.z;

    if (newPos.x == newPos.z)
        return;
    if (newPos.x > newPos.z) {
        if (newPos.x > 0)
            _rotation = -90;
        else
            _rotation = 0;
    } else {
        if (newPos.z > 0)
            _rotation = 180;
        else
            _rotation = 90;
    }
    
}

void Player::simulate()
{
    _frame++;
    if (_frame >= 40)
        _frame = 0;
}