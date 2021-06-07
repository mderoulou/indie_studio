/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Player Functions
*/

#include "Object.hpp"
#include "Manager.hpp"

Player::Player(rl::Vec3 pos, float scale, rl::Color color, std::string pathText)
{
    _color = color;
    _scale = scale;
    _rotation = 0.0f;
    _model = new rl::Model("../assets/steve-obj/steve.glb");
    _texture = new rl::Texture(pathText);
    _model->setMaterialTexture(0, _texture);
}

Player::Player(rl::Vec3 pos, float scale, rl::Color color)
{
    int count = 0;

    _pos = rl::Vec3(pos);
    _color = rl::Color(color);
    _rotation = 0;
    _scale = scale;
    _model = new rl::Model("../assets/steve-obj/steve.glb");
    _texture = new rl::Texture("../assets/steve-obj/player-name/skin.png");
    _model->setMaterialTexture(0, _texture);
    _frame = 0;
    _anim = new rl::ModelAnimation("../assets/steve-obj/steve.glb", &count);

}

Player::~Player()
{
    delete _model;
    delete _texture;
}

void Player::render()
{
    _model->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
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
    return;
    _frame++;
    _anim->update(_model, 0, _frame);
    if (_frame >= _anim->getFrameCount(0))
        _frame = 0;
    return;
}