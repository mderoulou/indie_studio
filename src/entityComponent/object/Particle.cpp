/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Particle
*/

#include "Particle.hpp"

Particle::Particle(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture, int life)
    : Cube(pos, size, color, scene)
{
    makeObj(texture, life);
}

Particle::Particle(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<rl::Model> model, int life) {
    _pos = rl::Vec3(pos);
    _life = life;
    _scene = scene;
    _color = color;
    _scale = scale;
    _model = model;
    _isSolid = false;
    _boundingBox._bd.min = pos-scale;
    _boundingBox._bd.max = pos+scale;
}

Particle::~Particle()
{
}

bool Particle::explode(Bomb *other) {
    rl::Vec3 d = _pos - other->_pos;
    float norm = pow(d[0]*d[0]+d[1]*d[1]+d[2]*d[2], 0.5);
    d[1] += 0.5;
    d /= norm;
    _v += d/2;
    return false;
}

void Particle::makeObj(std::shared_ptr<rl::Texture> texture, int life)
{
    _life = life;
    _texture = texture;
    _isSolid = false;
    _boundingBox._bd.min = _pos-_size/2;
    _boundingBox._bd.max = _pos+_size/2;
}

void Particle::render(rl::Camera3d *cam)
{
    if (_texture)
        _texture->drawTexture(_pos, _size, _color);
    else if (_model)
        _model->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
}

void Particle::simulate() {
    _life--;
    if (_life <= 0)
        _toRemove = true;
    // physic
    _v.x += _acc.x;
    _v.y += _acc.y;
    _v.z += _acc.z;

    _v.x *= 0.99;
    _v.y *= 0.99;
    _v.z *= 0.99;
    _acc.x = 0;
    _acc.y = -1/60.0;
    _acc.z = 0;

    //collide with Solid Object
    rl::Vec3 colideSize = {3, 3, 3};
    rl::Vec3 pCenter = (rl::Vec3(_boundingBox._bd.min) + rl::Vec3(_boundingBox._bd.max))/2;
    rl::Vec3 pSize = rl::Vec3(_boundingBox._bd.max) - rl::Vec3(_boundingBox._bd.min);
    std::vector<AObject *> vec = _manager->_PhysXTree->getInArea(pCenter, colideSize);

    for (AObject *&obj : vec) {
        if (obj == this)
            continue;
        if (_boundingBox.checkColissionBox(&obj->_boundingBox)) {
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
                _v[axe] *= -0.1;
            }
            _v[(axe+1)%3] *= 0.95;
            _v[(axe+2)%3] *= 0.95;
            move(dd*-0.1);
        }
    }

    move(_v);
}
