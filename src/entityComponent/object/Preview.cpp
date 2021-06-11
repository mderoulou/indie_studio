/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Preview
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

Preview::Preview(rl::Color color)
{
    _pos = rl::Vec3(7.5,2,13);
    _scene = 5;
    _color = color;
    _scale = 1;
    _rotation = -170;
    _texture = new rl::Texture("../assets/skins/skin.png");
    this->loadAnims();
}

void Preview::loadAnims()
{
    int count = 41;
    std::ostringstream objPath("");

    for (int i = 1; i < count; i++) {
        if (i < 10)
            objPath << "../assets/steve-obj/anims/steve_0" << i << ".glb";
        else
            objPath << "../assets/steve-obj/anims/steve_" << i << ".glb";
        _models.push_back(new rl::Model(objPath.str().c_str()));
        objPath.str("");
        objPath.clear();
    }
    for (auto model : _models)
        model->setMaterialTexture(0, _texture);
}

void Preview::setTexture(const std::string filename)
{
    delete _texture;
    _texture = new rl::Texture(filename.c_str());
    for (auto model : _models)
        model->setMaterialTexture(0, _texture);
}

Preview::~Preview()
{
    // TODO: Delete model
    delete _texture;
}

void Preview::move(rl::Vec3 newPos)
{
    AObject::move(newPos);
}

void Preview::render(rl::Camera3d *cam)
{
    cam->beginMode();

    if (_frame < 0 || _frame > 40) {
        cam->endMode();
        return;
    }
    _models[(int)_frame]->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
    cam->endMode();
}

void Preview::simulate()
{
    _frame += 0.5;

    if (_frame >= 40)
        _frame = 0;
    else if (_frame <= 0)
        _frame = 0;
}