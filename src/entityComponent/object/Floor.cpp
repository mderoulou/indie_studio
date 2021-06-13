/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include "Floor.hpp"

Floor::Floor(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture)
    : Cube(pos, size, color, scene)
{
    makeObj(texture);
}

Floor::Floor(std::shared_ptr<ByteObject> obj, std::shared_ptr<rl::Texture> texture)
{
    (*obj) >> _pos >> _size >> _color >> _scene;
    makeObj(texture);
}

void Floor::makeObj(std::shared_ptr<rl::Texture> texture){
    rl::Mesh mesh(_size.x, _size.y, _size.z);
    _isBreakable = false;
    _texture = texture;
    _isSolid = true;
    _boundingBox._bd.min = _pos-_size/2;
    _boundingBox._bd.max = _pos+_size/2;
}

Floor::~Floor() {
}

void Floor::render(rl::Camera3d *cam)
{
    _texture->drawTexture(_pos, _size, _color);
}

std::shared_ptr<ByteObject> Floor::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    
    (*obj) << ByteObject::FLOOR << _pos << _size << _color << _scene;
    return obj;
}