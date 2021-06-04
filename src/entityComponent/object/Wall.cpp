/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "Object.hpp"
#include "Manager.hpp"

Wall::Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color, std::string path, std::string texturePath)
    : Cube(pos, size, color)
{
    model = new rl::Model(path);
    texture = new rl::Texture(texturePath);
    SetMaterialTexture(&model->getModel().materials[0], MAP_DIFFUSE, texture->getTexture());
}

void Wall::render()
{
    model->draw(pos, size.x, color);
}