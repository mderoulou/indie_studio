/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Cube Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"

Wall::Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture)
    : Cube(pos, size, color, scene)
{
    makeObj(texture);
}

Wall::Wall(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Texture> texture)
{
    (*obj) >> _pos;
    (*obj) >> _size;
    (*obj) >> _color;
    (*obj) >> _scene;
    makeObj(texture);
}

void Wall::makeObj(std::shared_ptr<rl::Texture> texture)
{
    rl::Mesh mesh(_size.x, _size.y, _size.z);
    _isBreakable = false;
    _texture = texture;
    _isSolid = true;
    _boundingBox._bd.min = _pos-_size/2;
    _boundingBox._bd.max = _pos+_size/2 + rl::Vec3(0, 1, 0);
}

bool Wall::explode(Bomb *bombe) {
    return true;
}

void Wall::render(rl::Camera3d *cam)
{
    _texture->drawTexture(_pos, _size, _color);
}

std::shared_ptr<ByteObject> Wall::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    
    (*obj) << ByteObject::WALL << _pos << _size << _color << _scene;
    return obj;
}