/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "Object.hpp"
#include "Manager.hpp"

Cube::Cube(rl::Vec3 pos, rl::Vec3 size, rl::Color color)
{
    this->pos = rl::Vec3(pos);
    this->size = rl::Vec3(size);
    this->color = rl::Color(color);
}

void Cube::render()
{
    this->pos.drawCube(this->size, this->color);
}

