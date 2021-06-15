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

void ControlsAI::simulate() {
    _frame = _player->_manager->_frame;
    rl::Vec3 pos = {(float)round((*_player)[0]), 0, (float)round((*_player)[2])};
    auto &map = _player->_manager->_AImapValues;
    rl::Vec3 axis[5] = {
        {1, 0, 0},
        {-1, 0, 0},
        {0, 0, 1},
        {0, 0, -1},
        {0, 0, 0},
    };

    int best = map[(int)pos[0]][(int)pos[2]];
    int bestID = 4;
    for (int axeID = 0; axeID < 4; axeID++) {
        rl::Vec3 vec = axis[axeID] + pos;
        if (map[(int)pos[0]][(int)pos[2]] < best) {
            best = map[(int)pos[0]][(int)pos[2]];
            bestID = axeID;
        }
    }
    _axis = axis[bestID];
    std::cout << "simulate" << std::endl;
}

float ControlsAI::isKeyUp() {
    if (_frame != _player->_manager->_frame)
        simulate();
    return abs(-_axis[2]);
}

float ControlsAI::isKeyDown() {
    if (_frame != _player->_manager->_frame)
        simulate();
    return abs(_axis[2]);
}

float ControlsAI::isKeyLeft() {
    if (_frame != _player->_manager->_frame)
        simulate();
    return abs(-_axis[0]);
}

float ControlsAI::isKeyRight() {
    if (_frame != _player->_manager->_frame)
        simulate();
    return abs(_axis[0]);
}

int ControlsAI::isKeyUse() {
    if (_frame != _player->_manager->_frame)
        simulate();
    return _use;
}


