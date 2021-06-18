/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Preview
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

Preview::Preview(rl::Vec3 pos, float scale, int scene, float rotation, rl::Color color, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models)
{
    _pos = pos; //rl::Vec3(7.5,2,13);
    _scene = scene;
    _color.a = color.a;
    _color.r = color.r;
    _color.g = color.g;
    _color.b = color.b;
    _scale = scale;
    _rotation = rotation;//-170
    _texture = std::make_shared<rl::Texture>("assets/skins/skin.png");
    _models = models;
    _disabled = false;
}

void Preview::setTexture(const std::string filename)
{
    _texture = std::make_shared<rl::Texture>(filename.c_str());
    for (auto model : *_models)
        model->setMaterialTexture(0, _texture);
}

void Preview::move(rl::Vec3 newPos)
{
    AObject::move(newPos);
}

void Preview::render(rl::Camera3d *cam)
{
    if (_frame < 0 || _frame > 40 || _disabled)
        return;
    for (auto model : *_models)
        model->setMaterialTexture(0, _texture);
    (*_models)[(int)_frame]->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
}

void Preview::simulate()
{
    _frame += 0.5;

    if (_frame >= 40)
        _frame = 0;
    else if (_frame <= 0)
        _frame = 0;
}