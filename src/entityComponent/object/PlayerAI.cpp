/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Ia
*/

#include "../Manager.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <memory>
#define _USE_MATH_DEFINES 
#include <cmath>

#ifdef _WIN32
#define M_PI 3.14159265359
#endif


PlayerAI::PlayerAI(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<Controls> controls, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::string pathText) : 
    Player(pos, scale, color, scene, controls, models, pathText)
{

}

PlayerAI::PlayerAI(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::shared_ptr<Controls> controls) : 
    Player(obj, models, controls)
{
}

PlayerAI *PlayerAI::factory(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models) {
    std::cout << "load IA" << std::endl;
    int type;
    *obj >> type;
    std::shared_ptr<ControlsAI> controls = std::make_shared<ControlsAI>();
    PlayerAI *p = new PlayerAI(obj, models, controls);
    controls->setPlayer(p);
    return p;
}

PlayerAI *PlayerAI::factory(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::string pathText) {
    std::cout << "create IA" << std::endl;
    
    std::shared_ptr<ControlsAI> controls = std::make_shared<ControlsAI>();
    PlayerAI *p = new PlayerAI(pos, scale, color, scene, controls, models, pathText);
    controls->setPlayer(p);
    return p;
}

std::shared_ptr<ByteObject> PlayerAI::dump() {
    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    *obj << ByteObject::PLAYERAI;
    std::cout << "dump IA" << std::endl;
    *obj = *obj + *Player::dump();
    return obj;
}

// AI CONTROLLER

ControlsAI::ControlsAI() :
    Controls(-1)
{
}

void ControlsAI::setPlayer(PlayerAI *player) {
    _player = player;
}

#define PYTAGORE(x, y, z) (pow((float)(x)*(x)+(y)*(y)+(z)*(z), 0.5))

void ControlsAI::simulate() {
    _frame = _player->_manager->_frame;
    rl::Vec3 pos = _player->boudingBoxCenter() + rl::Vec3(0.5, 0, 0.5);
    auto &map = _player->_manager->_AImapValues;
    auto &typeMap = _player->_manager->_AImap;
    rl::Vec3 axis[5] = {
        {0, 0, 0},
        {0, 0, -1},
        {-1, 0, 0},
        {1, 0, 0},
        {0, 0, 1},
    };

    bool safe = true;
    int best = map[(int)pos[0]][(int)pos[2]];
    int bestID = 0;
    for (int axeID = 1; axeID < 5; axeID++) {
        rl::Vec3 vec = axis[axeID] + pos;
        if (map[(int)vec[0]][(int)vec[2]] < best) {
            best = map[(int)vec[0]][(int)vec[2]];
            bestID = axeID;
        }
        if (typeMap[(int)vec[0]][(int)vec[2]] & ControlsAI::cellType::WILLDIESOON)
            safe = false;

    }


    rl::Vec3 target = {(int)pos[0], 0, (int)pos[2]};
    target += axis[bestID];

    _axis = target - _player->_pos;
    _use = false;
    if (best < 0 && !(_frame % 2) && bestID == 0 && !(typeMap[(int)pos[0]][(int)pos[2]] & ControlsAI::cellType::POWERUP) && safe) {
        _use = true;
        _player->_v = {0, 0, 0};
    }
  
}

float ControlsAI::isKeyUp() {
    if (_frame != _player->_manager->_frame)
        simulate();
    if (_axis[2] < 0)
        return -_axis[2];
    return 0;
}

float ControlsAI::isKeyDown() {
    if (_frame != _player->_manager->_frame)
        simulate();
    if (_axis[2] > 0)
        return _axis[2];
    return 0;
}

float ControlsAI::isKeyLeft() {
    if (_frame != _player->_manager->_frame)
        simulate();
    if (_axis[0] < 0)
        return -_axis[0];
    return 0;
}

float ControlsAI::isKeyRight() {
    if (_frame != _player->_manager->_frame)
        simulate();
    if (_axis[0] > 0)
        return _axis[0];
    return 0;
}

int ControlsAI::isKeyUse() {
    if (_frame != _player->_manager->_frame)
        simulate();
    return _use;
}


