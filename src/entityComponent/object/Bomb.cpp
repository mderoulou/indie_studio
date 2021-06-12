/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(rl::Vec3 pos, float scale, rl::Color color, int scene, float time, std::shared_ptr<rl::Model> model, Player *player)
{
    _player = player;
    _pos = rl::Vec3(pos);
    _scene = scene;
    _color = color;
    _scale = scale;
    _explosed = false;
    _time = time;
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
    _time = 0;
    std::cout << "explode bomb" << std::endl;
    return true;
}


void Bomb::move(rl::Vec3 newPos)
{
    AObject::move(newPos);
}

void Bomb::simulate()
{
    bool debug = true;

    _time -= 1;
    
    if (debug)
        std::cout << "Bomb time : " << _time << std::endl;
    
    if (_time % 6 == 0){
        _scale += 0.01;
        _boundingBox._bd.min = _pos-_scale;
        _boundingBox._bd.max = _pos+_scale;
    }

    if (_time <= 0) {
        // explode the bomb
        std::cout << "BOM !" << std::endl;
        rl::Vec3 centered_pos = _pos;
        rl::Vec3 offset = {0, 0, 0};
        rl::Vec3 treeZone = {0.5, 0.5, 0.5};
        auto &PhysXTree = _manager->_PhysXTree;

        rl::Vec3 axis[4] = {
            {1, 0, 0},
            {-1, 0, 0},
            {0, 0, 1},
            {0, 0, -1},
        };

        for (int axis_nb = 0; axis_nb < 4; axis_nb++){
            int x = 0;
            offset = centered_pos;
            for (int i = 0; i <= _explosionRadius; i++) {
                auto vec = PhysXTree->getInArea(offset, treeZone);
                bool wilbreak = false;
                for (auto &obj : vec){
                    if (obj == this)
                        continue;
                    if (obj->explode(this))
                        wilbreak = true;
                    std::cout << "hit" << std::endl;
                }
                if (wilbreak)
                    goto next;
                offset += axis[axis_nb];
            }
            next:;
        }
        _explosed = true;
        _toRemove = true;
    }


    // physic
    _v.x += _acc.x;
    _v.y += _acc.y;
    _v.z += _acc.z;

    _v.x *= 0.8;
    _v.y *= 0.99;
    _v.z *= 0.8;
    _acc.x = 0;
    _acc.y = -1/60.0;
    _acc.z = 0;

    //collide with Solid Object
    rl::Vec3 colideSize = {3, 3, 3};
    rl::Vec3 pCenter = (rl::Vec3(_boundingBox._bd.min) + rl::Vec3(_boundingBox._bd.max))/2;
    rl::Vec3 pSize = rl::Vec3(_boundingBox._bd.max) - rl::Vec3(_boundingBox._bd.min);
    std::vector<AObject *> vec = _manager->_PhysXTree->getInArea(pCenter, colideSize);
    static int a = 0;
    _manager->_cam->beginMode();

    _boundingBox.draw({0, 255, 0, 255});
    for (AObject *&obj : vec) {
        if (obj == this)
            continue;
        obj->_boundingBox.draw({255, 0, 0, 255});
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
                _v[axe] *= 0.1;
            }
            move(dd*-0.1);
        }
        a++;
    }

    _manager->_cam->endMode();
    move(_v);

}

void Bomb::render(rl::Camera3d *cam)
{
    cam->beginMode();
    _model->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
    cam->endMode();
}