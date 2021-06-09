/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** RayLib Ray Class
*/

#ifndef RL_RAY_
#define RL_RAY_

#include "raylib.h"
#include "BoundingBox.hpp"
#include "Camera.hpp"

namespace rl {

class Ray
{
    public:
        Ray(rl::Vec2 mousePos, rl::Camera3d cam);
        
        void draw(rl::Color color);

        bool checkColissionSphere(rl::Vec3 center, float radius);
        bool checkColissionBox(rl::BoundingBox *box);

        static void openUrl(const std::string &url) { ::OpenURL(url.c_str()); };
    private:
        ::Ray _ray;
};

}

#endif