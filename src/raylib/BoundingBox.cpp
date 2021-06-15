/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** RayLib BoudingBox Functions
*/

#include "BoundingBox.hpp"

rl::BoundingBox::BoundingBox(rl::Vec3 max, rl::Vec3 min)
{
    _bd.max = max;
    _bd.min = min;
}

void rl::BoundingBox::draw(rl::Color color)
{
    DrawBoundingBox(_bd, color);
}

bool rl::BoundingBox::checkColissionBox(rl::BoundingBox *box)
{
    return CheckCollisionBoxes(_bd, box->getBox());
}

bool rl::BoundingBox::checkColissionSphere(rl::Vec3 pos, float radius)
{
    return CheckCollisionBoxSphere(_bd, pos, radius);
}

void rl::BoundingBox::changeBox(rl::Vec3 max, rl::Vec3 min)
{
    _bd.max = max;
    _bd.min = min;
}