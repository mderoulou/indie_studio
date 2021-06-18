/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(rl::Vec3 pos, float scale, rl::Color color, int scene, float time, std::shared_ptr<rl::Model> model, Player *player, int explosionRadius)
{
    _explosionRadius = explosionRadius;
    _player = player;
    _pos = rl::Vec3(pos);
    _scene = scene;
    _color = color;
    _scale = scale;
    _explosed = false;
    _time = time;
    _maxTime = time;
    _model = model;
    _player->_bombCount += 1;
    _isSolid = true;
    _boundingBox._bd.min = pos-scale;
    _boundingBox._bd.max = pos+scale;
}

Bomb::~Bomb() {
    _player->_bombCount -= 1;
}

bool Bomb::explode(Bomb *other) {
    rl::Vec3 d = _pos - other->_pos;
    float norm = pow(d[0]*d[0]+d[1]*d[1]+d[2]*d[2], 0.5);
    d /= norm;
    d[1] = 0.4;
    _v += d/2;
    return false;
}


void Bomb::move(rl::Vec3 newPos)
{
    AObject::move(newPos);
}

void Bomb::simulate()
{
    _time -= 1;
    
    if (_time % 6 == 0){
        _scale += 0.01;
        _boundingBox._bd.min = _pos-_scale;
        _boundingBox._bd.max = _pos+_scale;
    }

    if (_time <= 0) {
        // explode the bomb
        _manager->_mm->playSound("tnt.ogg");

        rl::Vec3 centered_pos = boudingBoxCenter() + rl::Vec3(0, 2-_scale, 0);
        rl::Vec3 treeZone = {0.5, 2, 0.5};
        auto &PhysXTree = _manager->_PhysXTree;

        rl::Vec3 axis[4] = {
            {1, 0, 0},
            {-1, 0, 0},
            {0, 0, 1},
            {0, 0, -1},
        };

        std::shared_ptr<Particle> p = std::make_shared<Particle>(centered_pos-rl::Vec3(0, 2-_scale, 0), 0.4, rl::Color(255, 255, 255, 255), _scene, _manager->_bomberman->_t._smoke, rand()%60+60);
        _manager->addComponent(p, _scene);

        for (int axis_nb = 0; axis_nb < 4; axis_nb++){
            int x = 0;
            rl::Vec3 offset = centered_pos;
            for (int i = 0; i <= _explosionRadius; i++, offset += axis[axis_nb]) {
                auto vec = PhysXTree->getInArea(offset, treeZone);
                bool wilbreak = false;
                for (auto &obj : vec){
                    if (obj == this)
                        continue;
                    if (obj->explode(this))
                        wilbreak = true;
                }
                if (wilbreak)
                    goto next;
                if (i > 0){
                    std::shared_ptr<Particle> p = std::make_shared<Particle>(offset-rl::Vec3(0, 2-_scale, 0), 0.4, rl::Color(255, 255, 255, 255), _scene, _manager->_bomberman->_t._smoke, rand()%60+60);
                    _manager->addComponent(p, _scene);
                }
            }
            next:;
        }
        for (int i = 0; i < 32; i++){
            rl::Vec3 randvec = {
                (float)(rand()%128-64.0)/64,
                (float)(rand()%128-64.0)/64,
                (float)(rand()%128-64.0)/64};
            std::shared_ptr<Particle> p = std::make_shared<Particle>(_pos + randvec, 0.1, rl::Color(255, 255, 255, 255), _scene, _model, rand()%120+60);
            p->_v[0] = randvec[0];
            p->_v[1] = abs(randvec[1]);
            p->_v[2] = randvec[2];
            p->_v /= 2;
            _manager->addComponent(p, _scene);
        }

        _explosed = true;
        _toRemove = true;
    }


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
        if (obj == this || dynamic_cast<Bomb *>(obj))
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

void Bomb::render(rl::Camera3d *cam)
{
    _model->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
}