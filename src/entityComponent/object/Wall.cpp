/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"

Wall::Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color, bool isWall, int scene)
    : Cube(pos, size, color, scene)
{
    _texture = new rl::Texture("../assets/block/stone-bricks.png");
    rl::Mesh mesh(size.x, size.y, size.z);

    _isBreakable = isWall;
    _model = new rl::Model(mesh);
    _model->setMaterialTexture(0, _texture);

}

void Wall::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _texture->drawTexture(_pos, _size, _color);
    cam->endMode();
}