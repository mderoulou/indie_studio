/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"

Cube::Cube(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene)
{
    _scene = scene;
    this->_pos = rl::Vec3(pos);
    this->_size = rl::Vec3(size);
    this->_color = rl::Color(color);
}

void Cube::render(rl::Camera3d *cam)
{
    (void)cam;
    cam->beginMode();
    this->_pos.drawCube(this->_size, this->_color);
    cam->endMode();
}