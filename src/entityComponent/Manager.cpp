/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Manager Functions
*/

#include "Manager.hpp"

ComponentManager::ComponentManager()
{
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

}

void ComponentManager::draw(IObject *obj)
{
    
}