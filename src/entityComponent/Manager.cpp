/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Manager Functions
*/

#include "Manager.hpp"

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

void ComponentManager::setPos()
{

}

void ComponentManager::movePos()
{

}

void ComponentManager::renderAll()
{

}

void ComponentManager::handleEvent()
{

}

void ComponentManager::draw(IObject *obj)
{
    
}