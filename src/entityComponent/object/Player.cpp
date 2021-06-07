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
    _model->setMaterialTexture(0, _texture);
}

Player::Player(rl::Vec3 pos, float scale, rl::Color color)
{
    int count = 0;

    _pos = rl::Vec3(pos);
    _color = rl::Color(color);
    _scale = scale;
    _model = new rl::Model("../assets/steve-obj/steve.glb");
    _texture = new rl::Texture("../assets/steve-obj/player-name/skin.png");
    _model->setMaterialTexture(0, _texture);
    _frame = 0;
    _anim = new rl::ModelAnimation("../assets/steve-obj/steve.glb", &count);

}
/*
Player::Player(rl::Vec3 pos, float scale, rl::Color color)
{
    int count = 0;

    _pos = rl::Vec3(pos);
    _color = rl::Color(color);
    _scale = scale;
    _model = new rl::Model("../assets/test/guy.iqm");
    _texture = new rl::Texture("../assets/test/guytex.png");
    _model->setMaterialTexture(0, _texture);
    _frame = 0;
    _anim = new rl::ModelAnimation("../assets/test/guyanim.iqm", &count);

}*/

Player::~Player()
{
    delete _model;
    delete _texture;
}

void Player::render()
{
    _model->draw(_pos, _scale, _color);
}

void Player::simulate()
{
    _frame++;
    _anim->update(_model, 0, _frame);
    if (_frame >= _anim->getFrameCount(0))
        _frame = 0;
    return;
}