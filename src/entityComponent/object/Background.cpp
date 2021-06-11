/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** background Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include "Background.hpp"

Background::Background(rl::Vec3 pos, int scene)
{
    _model = std::make_shared<rl::Model>("../assets/background/stone-terrain.glb");
    _pos = rl::Vec3(pos);
    _color = rl::Color(255, 255, 255, 255);
    _scale = 0.8;
    _scene = scene;
}

void Background::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _model->drawEx(_pos, rl::Vec3(0, 1, 0), 0,  rl::Vec3(_scale, _scale, _scale), _color);
    cam->endMode();
}