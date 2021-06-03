/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** RayLib Ray Class
*/

#ifndef RL_RAY_
#define RL_RAY_

#include "rayLib.hpp"

namespace rl {

class BoundingBox;
class Camera3d;

class Ray
{
    public:
        Ray(rl::Vec2 mousePos, rl::Camera3d cam);
        
        void draw(rl::Color color);

        bool checkColissionSphere(rl::Vec3 center, float radius);
        bool checkColissionBox(rl::BoundingBox *box);
    private:
        ::Ray _ray;
};

}

#endif