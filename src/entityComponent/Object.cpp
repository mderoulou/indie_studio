/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#include "Object.hpp"

AObject::~AObject() {
    if (_isSolid)
        _manager->_PhysXTree->erase(this);
};