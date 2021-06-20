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

    std::shared_ptr<Particle> p = std::make_shared<Particle>(_pos + _size*(0.2/2), _size*0.8, rl::Color(200, 200, 200, 255), _scene, _texture, 120);
    _manager->addComponent(p, _scene);

    int r = rand() % 9;
    std::shared_ptr<PowerUp> powerUp;
    if (r == 0) {
        powerUp = std::make_shared<PowerBombsPower>(boudingBoxCenter(), 3, _manager->_bomberman->_t._power_size);
    } else if (r == 1) {
        powerUp = std::make_shared<PowerBombsCount>(boudingBoxCenter(), 3, _manager->_bomberman->_t._power_bomb);
    } else if (r == 2) {
        powerUp = std::make_shared<PowerSpeed>(boudingBoxCenter(), 3, _manager->_bomberman->_t._power_speed);
    } else {
        goto noPowerUp;
    }
    _manager->addComponent(powerUp, 3);
    noPowerUp:;

    _manager->_mm->playSound("wood.ogg");

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
    _texture->drawTexture(_pos, _size, _color);
}

std::shared_ptr<ByteObject> Box::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    
    (*obj) << ByteObject::BOX << _pos << _size << _color << _scene;
    return obj;
}
