/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "Object.hpp"
#include "Manager.hpp"

Wall::Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color)
    : Cube(pos, size, color)
{
    _atlas = new rl::Texture("../assets/block/cubicmap_atlas.png");
}

void Wall::render()
{
    _atlas->drawTexture(_pos, _size, _color);
}