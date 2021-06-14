/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#include <ostream>
#include "Object.hpp"

AObject::~AObject() {
};

bool AObject::explode(Bomb *bombe) {
    return false;
};

rl::Vec3 AObject::boudingBoxCenter() {
    return ((rl::Vec3)_boundingBox._bd.min + (rl::Vec3)_boundingBox._bd.max)/2;
}
