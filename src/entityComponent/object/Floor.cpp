/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include "Floor.hpp"

Floor::Floor(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture)
    : Cube(pos, size, color, scene)
{
    _texture = texture;
    rl::Mesh mesh(size.x, size.y, size.z);

    _isBreakable = false;
    _model = std::make_shared<rl::Model>(mesh);
    _model->setMaterialTexture(0, _texture);
    _isSolid = true;
    _boundingBox._bd.min = pos-size/2;
    _boundingBox._bd.max = pos+size/2;
}

void Floor::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _texture->drawTexture(_pos, _size, _color);
    cam->endMode();
}