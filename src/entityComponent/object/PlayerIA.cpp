/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Ia
*/

#include "../Object.hpp"
#include "../Manager.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <memory>
#define _USE_MATH_DEFINES 
#include <cmath>

#ifdef _WIN32
#define M_PI 3.14159265359
#endif

PlayerIA::PlayerIA(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::string pathText)
{
    _pos = pos;
    _scene = scene;
    _color = color;
    _scale = scale;
    _pathText = pathText;
    _texture = std::make_shared<rl::Texture>(_pathText);
    _rotation = 0;
    _frame = 0;
    makeObj(models);
}

PlayerIA::PlayerIA(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models)
{
    (*obj) >> _pos >> _v >> _acc >> _scale >> _rotation >> _frame >> _scene;

    makeObj(models);
    _pathText = std::string(&(obj->data[obj->cursor]));
    _texture = std::make_shared<rl::Texture>(_pathText);
}

void PlayerIA::makeObj(std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models)
{
    _isSolid = true;
    _boundingBox._bd.min = _pos + rl::Vec3{-0.25, 0.0, -0.25};
    _boundingBox._bd.max = _pos + rl::Vec3{0.25, 1.8, 0.25};
    _models = models;
}

std::shared_ptr<ByteObject> PlayerIA::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    std::vector<char> name;
    for (char &c : _pathText)
        name.push_back(c);
    name.push_back(0);
    *obj = ((*obj) << ByteObject::IA << _pos << _v << _acc << _scale << _rotation << _frame << _scene) + ByteObject(name, name.size());
    return obj;
}
