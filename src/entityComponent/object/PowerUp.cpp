/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** PowerUp
*/

#include "PowerUp.hpp"


PowerUp::PowerUp(rl::Vec3 pos, std::shared_ptr<rl::Model> model, int scene, float scale, rl::Color color)
{
    _pos = pos;
    _color = color;
    _scale = scale;
    _scene = scene;
    makeObj(model);
}

PowerUp::PowerUp(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model)
{
    (*obj) >> _pos >> _color >> _scale >> _scene;
    makeObj(model);
}

PowerUp::~PowerUp()
{
}

std::shared_ptr<PowerUp> PowerUp::factory(std::shared_ptr<ByteObject> &obj, Bomberman *b) {
    int type;
    *obj >> type;
    if (type == PowerUp::type::BOMBCOUNT) {
        return std::make_shared<PowerBombsCount>(obj, b->_t._power_bomb);
    } else if (type == PowerUp::type::BOMBPOWER) {
        return std::make_shared<PowerBombsPower>(obj, b->_t._power_size);
    } else if (type == PowerUp::type::SPEED) {
        return std::make_shared<PowerSpeed>(obj, b->_t._power_speed);
    } else {
        std::cerr << "invalid powerup type" << std::endl;
    }
    return std::make_shared<PowerUp>(obj, b->_t._smoke);
}

void PowerUp::makeObj(std::shared_ptr<rl::Model> model)
{
    _model = model;
    _isSolid = false;
    _boundingBox._bd.min = _pos-_scale/2;
    _boundingBox._bd.max = _pos+_scale/2;
}

void PowerUp::render(rl::Camera3d *cam)
{
    _model->drawEx(_pos+rl::Vec3(0, cos(_rotation/70)*0.25, 0), rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
}

std::shared_ptr<ByteObject> PowerUp::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    
    (*obj) << _pos << _color << _scale << _scene;
    return obj;
}

void PowerUp::apllyToPlayer(Player *p) {
    _manager->_mm->playSound("powerup.ogg");
}

void PowerUp::simulate()
{
    _rotation += 1;
    //collide with Solid Object
    rl::Vec3 colideSize = {3, 3, 3};
    rl::Vec3 pCenter = (rl::Vec3(_boundingBox._bd.min) + rl::Vec3(_boundingBox._bd.max))/2;
    rl::Vec3 pSize = rl::Vec3(_boundingBox._bd.max) - rl::Vec3(_boundingBox._bd.min);
    std::vector<AObject *> vec = _manager->_PhysXTree->getInArea(pCenter, colideSize);

    for (AObject *&obj : vec) {
        if (obj == this)
            continue;
        Player *p = dynamic_cast<Player *>(obj);

        if (p && _boundingBox.checkColissionBox(&obj->_boundingBox)) {
            _toRemove = true;
            apllyToPlayer(p);
            break;
        }
    }
}

// POWER UP BOMBE COUNT

PowerBombsCount::PowerBombsCount(rl::Vec3 pos, int scene, std::shared_ptr<rl::Model> model) :
    PowerUp(pos, model, scene)
{

}

PowerBombsCount::PowerBombsCount(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model) :
    PowerUp(obj, model)
{
}

std::shared_ptr<ByteObject> PowerBombsCount::dump() {
    auto obj = PowerUp::dump();
    std::shared_ptr<ByteObject> obj1 = std::make_shared<ByteObject>();
    *obj1 << ByteObject::POWERUP << PowerUp::type::BOMBCOUNT;
    *obj1 = *obj1 + *obj;
    return obj1;
}

void PowerBombsCount::apllyToPlayer(Player *p) {
    PowerUp::apllyToPlayer(p);
    p->_maxBombCount++;
}

// POWER UP BOMBE POWER

PowerBombsPower::PowerBombsPower(rl::Vec3 pos, int scene, std::shared_ptr<rl::Model> model) :
    PowerUp(pos, model, scene)
{

}

PowerBombsPower::PowerBombsPower(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model) :
    PowerUp(obj, model)
{
}

std::shared_ptr<ByteObject> PowerBombsPower::dump() {
    auto obj = PowerUp::dump();
    std::shared_ptr<ByteObject> obj1 = std::make_shared<ByteObject>();
    *obj1 << ByteObject::POWERUP << PowerUp::type::BOMBPOWER;
    *obj1 = *obj1 + *obj;
    return obj1;
}

void PowerBombsPower::apllyToPlayer(Player *p) {
    PowerUp::apllyToPlayer(p);
    p->_explosionRadius++;
}

// POWER UP SPEED

PowerSpeed::PowerSpeed(rl::Vec3 pos, int scene, std::shared_ptr<rl::Model> model) :
    PowerUp(pos, model, scene)
{
}

PowerSpeed::PowerSpeed(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model) :
    PowerUp(obj, model)
{
}

std::shared_ptr<ByteObject> PowerSpeed::dump() {
    auto obj = PowerUp::dump();
    std::shared_ptr<ByteObject> obj1 = std::make_shared<ByteObject>();
    *obj1 << ByteObject::POWERUP << PowerUp::type::SPEED;
    *obj1 = *obj1 + *obj;
    return obj1;
}

void PowerSpeed::apllyToPlayer(Player *p) {
    PowerUp::apllyToPlayer(p);
    p->_speedFactor += 0.1;
}

