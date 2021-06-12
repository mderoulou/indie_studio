/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Box
*/

#include "Box.hpp"

Box::Box(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture)
    : Cube(pos, size, color, scene)
{
    _isBreakable = true;
    _texture = texture;
    _isSolid = true;
    _boundingBox._bd.min = pos-size/2;
    _boundingBox._bd.max = pos+size/2 + rl::Vec3(0, 1, 0);
}

Box::~Box() {
}

bool Box::explode(Bomb *){
    _toRemove = true;
    std::cout << "explode" << std::endl;
    return true;
}


void Box::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _texture->drawTexture(_pos, _size, _color);
    cam->endMode();
}