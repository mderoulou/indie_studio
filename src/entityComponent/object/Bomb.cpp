/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(rl::Vec3 pos, float scale, rl::Color color, int scene, float time)
{
    _pos = rl::Vec3(pos);
    _scene = scene;
    _color = color;
    _scale = scale;
    _explosed = false;
    _time = time;
    _model = new rl::Model("../assets/block/tnt.glb");
}

void Bomb::move(rl::Vec3 newPos)
{
    AObject::move(newPos);
}

void Bomb::simulate()
{
    bool debug = true;

    if (_explosed)
        return;
    _time -= 1;
    
    if (debug)
        std::cout << "Bomb time : " << _time << std::endl;
    
    if (_time % 6 == 0)
        _scale += 0.01;

    if (_time <= 0) {
        std::cout << "BOM !" << std::endl;
        _scale = 0;
        _explosed = true;
    }
}

void Bomb::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _model->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
    cam->endMode();
}