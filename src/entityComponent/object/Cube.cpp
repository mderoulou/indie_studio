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
    this->_color.a = color.a;
    this->_color.r = color.r;
    this->_color.g = color.g;
    this->_color.b = color.b;
}

void Cube::render(rl::Camera3d *cam)
{
    this->_pos.drawCube(this->_size, this->_color);
}