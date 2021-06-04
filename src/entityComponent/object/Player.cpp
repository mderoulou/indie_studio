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
    _model = new rl::Model("../assets/steve-obj/steve.glb");
    _texture = new rl::Texture(pathText);
    SetMaterialTexture(&_model->getModel().materials[0], MAP_DIFFUSE, _texture->getTexture());
}

Player::Player(rl::Vec3 pos, float scale, rl::Color color)
{
    _pos = rl::Vec3(pos);
    _color = rl::Color(color);
    _scale = scale;
    _model = new rl::Model("../assets/steve-obj/steve.glb");
    _texture = new rl::Texture("../assets/steve-obj/player-name/skin.png");
    SetMaterialTexture(&_model->getModel().materials[0], MAP_DIFFUSE, _texture->getTexture());
}

Player::~Player()
{
    delete _model;
    delete _texture;
}

void Player::render()
{
    _model->draw(_pos, _scale, _color);
}