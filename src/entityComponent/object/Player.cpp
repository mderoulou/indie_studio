/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Player Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include "Bomb.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES 
#include <cmath>

#ifdef _WIN32
#define M_PI 3.14159265359
#endif

Player::Player(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<Controls> controls, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::string pathText)
{
    _pos = pos;
    _scene = scene;
    _color = color;
    _scale = scale;
    _pathText = pathText;
    _texture = std::make_shared<rl::Texture>(_pathText);
    _rotation = 0;
    _frame = 0;
    _controller = controls;
    makeObj(models);
}

Player::Player(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::shared_ptr<Controls> controls)
{
    (*obj) >> _pos >> _v >> _acc >> _isKeyUsed >> _scale >> _rotation >> _frame >> _isKeyboard >> _scene >> _explosionRadius >> _maxBombCount >> _speedFactor >> _rotation >> _deadVec >> _isDead >> _playerId;
    _controller = controls;
    makeObj(models);
    _pathText = std::string(&(obj->data[obj->cursor]));
    _texture = std::make_shared<rl::Texture>(_pathText);
}

std::shared_ptr<ByteObject> Player::dump()
{
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    std::vector<char> name;
    for (char &c : _pathText)
        name.push_back(c);  
    name.push_back(0);
    *obj = ((*obj) << ByteObject::PLAYER << _pos << _v << _acc << _isKeyUsed << _scale << _rotation << _frame << _isKeyboard << _scene << _explosionRadius << _maxBombCount << _speedFactor << _rotation << _deadVec << _isDead << _playerId) + ByteObject(name, name.size());
    return obj;
}

void Player::makeObj(std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models)
{
    _isSolid = true;
    _boundingBox._bd.min = _pos + rl::Vec3{-0.25, 0.0, -0.25};
    _boundingBox._bd.max = _pos + rl::Vec3{0.25, 1.8, 0.25};
    _models = models;
}

void Player::die() {
    for (int i = 0; i < 32; i++){
        rl::Vec3 randvec = {
            (float)(rand()%128-64.0)/64,
            (float)(rand()%128-64.0)/64,
            (float)(rand()%128-64.0)/64};
        std::shared_ptr<Particle> p = std::make_shared<Particle>(boudingBoxCenter()+rl::Vec3(0, 0.2, 0), rl::Vec3(0.1, 0.1, 0.1), rl::Color(255, 255, 255, 255), _scene, _manager->_bomberman->_t._redstone, rand()%120+60);
        p->_v[0] = randvec[0];
        p->_v[1] = abs(randvec[1])*2;
        p->_v[2] = randvec[2];
        p->_v /= 6;
        _manager->addComponent(p, _scene);
    }
    _isDead = true;
    _manager->_mm->playSound("hurt.ogg");
}

bool Player::explode(Bomb *other) {
    std::cout << "explode player" << std::endl;
    rl::Vec3 d = _pos - other->_pos;
    float norm = pow(d[0]*d[0]+d[1]*d[1]+d[2]*d[2], 0.5);
    //d = {d[0]/norm, 0, d[2]/norm};
    //_deadVec = {acos(d[0]/norm), acos(d[1]/norm), acos(d[2]/norm)};
    _deadVec = {-d[2], 0, -d[0]};
    _rotation = 0;
    d[1] += 1;
    d /= norm;
    _v += d/1.5;
    _color = {255, 128, 128, 255};
    die();
    return false;
}


void Player::render(rl::Camera3d *cam)
{

    if (_frame < 0 || _frame > 40)
        return;
    (*_models)[(int)_frame]->setMaterialTexture(0, _texture);
    (*_models)[(int)_frame]->drawEx(_pos, _direction, _rotation, rl::Vec3(_scale, _scale, _scale), _color);
}

void Player::move(rl::Vec3 newPos)
{
    AObject::move(newPos);
}

double findAngle(rl::Vec2 vec)
{
    double len = pow(pow(vec.x, 2) + pow(vec.y, 2), 0.5);
    double a1 = acosf(vec.x / len);
    if (vec.y < 0)
        a1 = -a1;
    return a1;
}

void Player::simulate()
{
    float acc_mult = 0.05 * _speedFactor;
    //std::cout << "[MANAGER] Moving Events!" << std::endl;

    // controller 
    bool hasMove = false;
    if (_isDead){
        _rotation = _rotation*0.9 + 90*0.1;
        _direction = _direction*0.9 + _deadVec*0.1;
        float norm = pow(_direction[0]*_direction[0]+_direction[1]*_direction[1]+_direction[2]*_direction[2], 0.5);
        rl::Vec3 randvec = {
            (float)(rand()%128-64.0)/64,
            (float)(rand()%128-64.0)/64,
            (float)(rand()%128-64.0)/64};
        std::shared_ptr<Particle> p = std::make_shared<Particle>(_pos+rl::Vec3(0, 0.2, 0), rl::Vec3(0.1, 0.1, 0.1), rl::Color(255, 50, 50, 255), _scene, _manager->_bomberman->_t._redstone, rand()%120+60);
        p->_v[0] = randvec[0];
        p->_v[1] = abs(randvec[1])*2;
        p->_v[2] = randvec[2];
        p->_v /= 6;
        _manager->addComponent(p, _scene);
        if (_deathTime <= 0)
            _toRemove = true;
        _deathTime--;
    } else if (_controller) {
        float mov = 0;
        if ((mov = _controller->isKeyUp()) != 0) { 
            _acc.z = -acc_mult * mov;
            hasMove = true;
        }
        if ((mov = _controller->isKeyDown()) != 0) {
            _acc.z = acc_mult * mov;
            hasMove = true;
        }
        if ((mov = _controller->isKeyLeft()) != 0) {
            _acc.x = -acc_mult * mov;
            hasMove = true;
        }
        if ((mov = _controller->isKeyRight()) != 0) {
            _acc.x = acc_mult * mov;
            hasMove = true;
        }

        float mv_speed = pow(pow(_acc.x, 2) + pow(_acc.z, 2), 0.5);
        if (mv_speed > acc_mult) {
            _acc.x = _acc.x/mv_speed*acc_mult;
            _acc.z = _acc.z/mv_speed*acc_mult;
        }

        float angle = -findAngle({_v.x, _v.z})*180/M_PI-90;

        while (_rotation - angle > 180) {
            _rotation -= 360; 
        }

        while (-_rotation + angle > 180) {
            _rotation += 360; 
        }


        if (std::isnormal(angle))
            _rotation = _rotation*0.8 + (angle)*0.2;
    
        auto vec = boudingBoxCenter();
        if (vec[1] > 2) {
            _pos[1] -= vec[1]-2;
        } else if (vec[1] < 0) {
            _pos[1] += 0-vec[1];
        }

    }
    physiX(acc_mult, hasMove);
}

void Player::physiX(float acc_mult, bool hasMove) {
        // player animation
    _frame += acc_mult * pow(pow(_v.x, 2) + pow(_v.z, 2), 0.5) * 100;
    if (!((int)_frame % 20)) {
    }
    

    if (_v.x*_v.x + _v.z*_v.z < 0.01 && _frame > 0 && !hasMove) {
        if ((int)_frame == 20)
            _frame = 0;
        if ((int)_frame % 20 > 10)
            _frame += 1;
        else
            _frame -= 1;
    }
    
    if (_frame >= 40)
        _frame = 0;
    else if (_frame <= 0)
        _frame = 0;


    _v.x += _acc.x;
    _v.y += _acc.y;
    _v.z += _acc.z;

    if (hasMove){
        _v.x *= 0.9;
        //_v.y *= 0.9;
        _v.z *= 0.9;
    }


    _acc.x = 0;
    _acc.y = -1/60.0;
    _acc.z = 0;

    //collide with Solid Object
    rl::Vec3 colideSize = {3, 3, 3};
    rl::Vec3 pCenter = (rl::Vec3(_boundingBox._bd.min) + rl::Vec3(_boundingBox._bd.max))/2;
    rl::Vec3 pSize = rl::Vec3(_boundingBox._bd.max) - rl::Vec3(_boundingBox._bd.min);
    std::vector<AObject *> vec = _manager->_PhysXTree->getInArea(pCenter, colideSize);

    for (AObject *&obj : vec) {
        if (obj != this && _boundingBox.checkColissionBox(&obj->_boundingBox)) {
            rl::Vec3 objSize = rl::Vec3(obj->_boundingBox._bd.max) - rl::Vec3(obj->_boundingBox._bd.min);
            
            rl::Vec3 objCenter = (rl::Vec3(obj->_boundingBox._bd.max) + rl::Vec3(obj->_boundingBox._bd.min))/2;
            rl::Vec3 d = pCenter-objCenter;

            char signe[3];
            for (int i = 0 ; i < 3; i++){
                signe[i] = d[i] > 0 ? 1 : -1;
                d[i] = abs(d[i]);
            }

            rl::Vec3 dd = d-((objSize+pSize)/2);

            float min = dd[0];
            int axe = 0;
            for (int i = 1; i < 3; i++)
                if (abs(dd[i]) < abs(min)){
                    min = dd[i];
                    axe = i;
                }
            for (int i = 0; i < 3; i++)
                if (i != axe){
                    dd[i] = 0;
                }
            
            for (int i = 0 ; i < 3; i++){
                dd[i] *= signe[i];
            }

            if (dd[axe] * _v[axe] > 0) {
                _v[axe] *= 0.1;
            }
            if (axe == 1){
                _v[(axe+1)%3] *= 0.8;
                _v[(axe+2)%3] *= 0.8;
            }
            move(dd*-1);
        }
    }
    move(_v);
}

void Player::handleEvent()
{
    if (_isDead)
        return;
    if (_controller && _controller->isKeyUse()) {
        if (!_isKeyUsed && _bombCount < _maxBombCount){
            this->_manager->addComponent(std::make_shared<Bomb>(_pos, 0.2, rl::Color(255, 255, 255, 255), _scene, 180, _manager->_bomberman->_t._tnt_a, this, _explosionRadius), _scene);
        }
        _isKeyUsed = true;
    } else {
        _isKeyUsed = false;
    }
}

