/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Player Functions
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES 
#include <cmath>

#ifdef _WIN32
#define M_PI 3.14159265359
#endif

Player::Player(rl::Vec3 pos, float scale, rl::Color color, std::string pathText, int scene, bool _isKeyboad)
{
    int count = 40;
    _scene = scene;
    _color = color;
    _scale = scale;
    _rotation = 0;
    _texture = new rl::Texture(pathText);
    if (_isKeyboad)
        _controller = new Keyboard(rl::Font());
    else
        _controller = new Gamepad(rl::Font());
    this->loadAnims();
    _isSolid = false;
    _boundingBox._bd.min = pos + rl::Vec3{-0.25, 0.0, -0.25};
    _boundingBox._bd.max = pos + rl::Vec3{0.25, 1.8, 0.25};

}

Player::Player(rl::Vec3 pos, float scale, rl::Color color, int scene, bool _isKeyboad)
{
    _pos = rl::Vec3(pos);
    _color = rl::Color(color);
    _rotation = 0;
    _scale = scale;
    _texture = new rl::Texture("../assets/skins/skin.png");
    _frame = 0;
    _scene = scene;
    if (_isKeyboad)
        _controller = new Keyboard(rl::Font());
    else
        _controller = new Gamepad(rl::Font());
    this->loadAnims();
    _isSolid = false;
    _boundingBox._bd.min = pos + rl::Vec3{-0.25, 0.0, -0.25};
    _boundingBox._bd.max = pos + rl::Vec3{0.25, 1.8, 0.25};
}

Player::~Player()
{
    delete _texture;
}

void Player::loadAnims()
{
    int count = 41;
    std::ostringstream objPath("");

    for (int i = 1; i < count; i++) {
        if (i < 10)
            objPath << "../assets/steve-obj/anims/steve_0" << i << ".glb";
        else
            objPath << "../assets/steve-obj/anims/steve_" << i << ".glb";
        //std::cout << objPath.str().c_str() << std::endl;
        _models.push_back(new rl::Model(objPath.str().c_str()));
        objPath.str("");
        objPath.clear();
    }
    for (auto model : _models)
        model->setMaterialTexture(0, _texture);
}

void Player::render(rl::Camera3d *cam)
{
    cam->beginMode();

    if (_frame < 0 || _frame > 40) {
        cam->endMode();
        return;
    }
    _models[(int)_frame]->drawEx(_pos, rl::Vec3(0, 1, 0), _rotation, rl::Vec3(_scale, _scale, _scale), _color);
    cam->endMode();
}

void Player::move(rl::Vec3 newPos)
{
    AObject::move(newPos);
    /*if (newPos.x == newPos.z)
        return;
    if (newPos.x > newPos.z) {
        if (newPos.x > 0)
            _rotation = -90;
        else
            _rotation = 0;
    } else {
        if (newPos.z > 0)
            _rotation = 180;
        else
            _rotation = 90;
    }*/
    
}

double findAngle(rl::Vec2 vec) {
    double len = pow(pow(vec.x, 2) + pow(vec.y, 2), 0.5);
    double a1 = acosf(vec.x / len);
    if (vec.y < 0)
        a1 = -a1;
    return a1;
}

void Player::simulate()
{
    float acc_mult = 0.05; 

    //std::cout << "[MANAGER] Moving Events!" << std::endl;

    // controller 
    if (_controller) {
        float mov = 0;
        if (!_controller->initialized)
            _controller->init();
        if ((mov = _controller->isKeyUp()) != 0) { 
            _acc.z = -acc_mult * mov;
        }
        if ((mov = _controller->isKeyDown()) != 0) {
            _acc.z = acc_mult * mov;
        }
        if ((mov = _controller->isKeyLeft()) != 0) {
            _acc.x = -acc_mult * mov;
        }
        if ((mov = _controller->isKeyRight()) != 0) {
            _acc.x = acc_mult * mov;
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
        

        // player animation
        _frame += acc_mult * pow(pow(_v.x, 2) + pow(_v.z, 2), 0.5) * 100;
       
        if (_v.x*_v.x + _v.z*_v.z < 0.01 && _frame > 0 && mov == 0) {
            if ((int)_frame == 20)
                _frame = 0;
            if ((int)_frame%20 > 10)
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

        _v.x *= 0.8;
        _v.y *= 0.99;
        _v.z *= 0.8;
        _acc.x = 0;
        _acc.y = -1/60.0;
        _acc.z = 0;

        //collide with Solid Object
        rl::Vec3 colideSize = {2, 2, 2};
        rl::Vec3 pCenter = (rl::Vec3(_boundingBox._bd.min) + rl::Vec3(_boundingBox._bd.max))/2;
        rl::Vec3 pSize = rl::Vec3(_boundingBox._bd.max) - rl::Vec3(_boundingBox._bd.min);
        std::vector<AObject *> vec = _manager->_PhysXTree->getInArea(pCenter, colideSize);
        static int a = 0;
        _manager->_cam->beginMode();

        _boundingBox.draw({0, 255, 0, 255});
        for (AObject *&obj : vec) {
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

                std::cout << "objSize+pSize " << (objSize+pSize)[0] << " " << (objSize+pSize)[1] << " " << (objSize+pSize)[2] <<std::endl;
                std::cout << "objcenter " << objCenter[0] << " " << objCenter[1] << " " << objCenter[2] <<std::endl;
                std::cout << "playercenter " << pCenter[0] << " " << pCenter[1] << " " << pCenter[2] <<std::endl;
                std::cout << "d " << d[0] << " " << d[1] << " " << d[2] <<std::endl;
                std::cout << "dd " << dd[0] << " " << dd[1] << " " << dd[2] <<std::endl;

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

                std::cout << "min" << axe << " " << min << std::endl;
                std::cout << "dd " << dd[0] << " " << dd[1] << " " << dd[2] <<std::endl;
                
                //dd *= 1;
                _v[axe] *= 0.1;
                move(dd*-1);
                
                std::cout << "centers " << pCenter[axe] << " " << objCenter[axe] << std::endl;

                std::cout << axe << " "<<((objSize+pSize)/2)[axe] << " " << d[axe] << " " << dd[axe] << " " << objSize[axe] << " " << pSize[axe] << " " << (objSize+pSize)[axe] << std::endl;

                std::cout << std::endl;
            }
            a++;
        }
                std::cout << std::endl;
                std::cout << std::endl;

        _manager->_cam->endMode();
        move(_v);
    }

}