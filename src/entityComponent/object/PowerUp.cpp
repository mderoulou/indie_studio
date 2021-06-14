/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** PowerUp
*/

#include "PowerUp.hpp"

PowerUp::PowerUp(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture)
    : Cube(pos, size, color, scene)
{
    makeObj(texture);
}

PowerUp::PowerUp(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Texture> texture)
{
    (*obj) >> _pos >> _size >> _color >> _scene;
    makeObj(texture);
}

PowerUp::~PowerUp()
{
}

bool PowerUp::explode(Bomb *){
    _toRemove = true;
    Particle *p = new Particle(_pos + _size*(0.2/2), _size*0.8, rl::Color(200, 200, 200, 255), _scene, _texture, 120);
    _manager->addComponent(p, _scene);
    return true;
}

void PowerUp::makeObj(std::shared_ptr<rl::Texture> texture)
{
    _isBreakable = true;
    _texture = texture;
    _isSolid = true;
    _boundingBox._bd.min = _pos-_size/2;
    _boundingBox._bd.max = _pos+_size/2 + rl::Vec3(0, 1, 0);
}

void PowerUp::render(rl::Camera3d *cam)
{
    _texture->drawTexture(_pos, _size, _color);
}

std::shared_ptr<ByteObject> PowerUp::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    
    (*obj) << ByteObject::POWERUP << _pos << _size << _color << _scene;
    return obj;
}