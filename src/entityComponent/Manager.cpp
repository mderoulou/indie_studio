/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Manager Functions
*/

#include "Manager.hpp"

ComponentManager::ComponentManager()
{
    _gp = new Gamepad(rl::Font());
}

ComponentManager::~ComponentManager()
{
    this->clearComponents();
}

void ComponentManager::addComponent(IObject *obj)
{
    _objs.push_back(obj);
}

void ComponentManager::clearComponents()
{
    _objs.clear();
}

void ComponentManager::simulate()
{
    if (!_gp->initialized)
        _gp->init();
    for (auto obj : _objs) {
        obj->simulate();
    }
}

void ComponentManager::renderAll()
{
    for (auto obj : _objs) {
        obj->render();
    }
}

void ComponentManager::handleEvent()
{
    // Movement Event
    rl::Vec3 newPos(0, 0, 0);
    float mov;

    if (!_gp->initialized)
        return;
    if ((mov = _gp->isKeyUp()) != 0) {
        newPos.z = -0.1f * mov;
        mov = 0;
    }
    if ((mov = _gp->isKeyDown()) != 0) {
        newPos.z = 0.1f * mov;
        mov = 0;
    }
    if ((mov = _gp->isKeyLeft()) != 0) {
        newPos.x = -0.1f * mov;
        mov = 0;
    }
    if ((mov = _gp->isKeyRight()) != 0) {
        newPos.x = 0.1f * mov;
        mov = 0;
    }
    
    std::cout << " move = x :"  << newPos.x << " y:" << newPos.y << "z:" << newPos.z << std::endl;
    for (auto obj : _objs) {
        obj->move(newPos);
    }
}