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
    rl::Mesh mesh(2.0f, 2.0f, 2.0f);

    _model = new rl::Model(mesh);
    _model->setMaterialTexture(0, _atlas);

}

void Wall::render()
{
    _atlas->drawTexture(_pos, _size, _color);
}