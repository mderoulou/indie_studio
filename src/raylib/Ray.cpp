/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** RayLib Ray Functions
*/

#include "Ray.hpp"

rl::Ray::Ray(rl::Vec2 mousePos, rl::Camera3d cam)
{
    _ray = GetMouseRay(mousePos, cam);
}

void rl::Ray::draw(rl::Color color)
{
    DrawRay(_ray, color);
}

bool rl::Ray::checkColissionSphere(rl::Vec3 pos, float radius)
{
    //return CheckCollisionRaySphere(_ray, pos, radius);
    (void)pos;
    (void)radius;
    return false;
}

bool rl::Ray::checkColissionBox(rl::BoundingBox *box)
{
    //return CheckCollisionRayBox(_ray, box->getBox());
    (void)box;
    return false;
}