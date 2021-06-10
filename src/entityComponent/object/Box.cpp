/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Box
*/

#include "Box.hpp"

Box::Box(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene)
    : Cube(pos, size, color, scene)
{
    _texture = new rl::Texture("../assets/block/wood.png");
    rl::Mesh mesh(size.x, size.y, size.z);

    _isBreakable = true;
    _model = new rl::Model(mesh);
    _model->setMaterialTexture(0, _texture);
    _isSolid = true;
    _boundingBox._bd.min = pos-size/2;
    _boundingBox._bd.max = pos+size/2;
}

void Box::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _texture->drawTexture(_pos, _size, _color);
    cam->endMode();
}