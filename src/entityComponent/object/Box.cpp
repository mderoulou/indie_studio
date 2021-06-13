/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Box
*/

#include "Box.hpp"

Box::Box(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture)
    : Cube(pos, size, color, scene)
{
    makeObj(texture);
}

Box::Box(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Texture> texture)
{
    (*obj) >> _pos >> _size >> _color >> _scene;
    makeObj(texture);
}

Box::~Box()
{
}

bool Box::explode(Bomb *){
    _toRemove = true;
    std::cout << "explode" << std::endl;
    return true;
}

void Box::makeObj(std::shared_ptr<rl::Texture> texture)
{
    _isBreakable = true;
    _texture = texture;
    _isSolid = true;
    _boundingBox._bd.min = _pos-_size/2;
    _boundingBox._bd.max = _pos+_size/2 + rl::Vec3(0, 1, 0);
}

void Box::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _texture->drawTexture(_pos, _size, _color);
    cam->endMode();
}

std::shared_ptr<ByteObject> Box::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    
    (*obj) << ByteObject::BOX << _pos << _size << _color << _scene;
    return obj;obj;
}