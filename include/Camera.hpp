/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Camera Class
*/

#ifndef RL_CAMERA_
#define RL_CAMERA_

#include "rayLib.hpp"

namespace rl {

// Need this thing or it broke
class Vec2;
class Vec3;


class Camera2d : public ::Camera2D
{
    public:
        Camera2d();
        Camera2d(rl::Vec2 offset, rl::Vec2 target, float rotation, float zoom);
        ~Camera2d() {};
};

class Camera3d : public ::Camera3D
{
    public:
        Camera3d();
        Camera3d(rl::Vec3 pos, rl::Vec3 target, rl::Vec3 up, float fovy, int proj);
        ~Camera3d() {};

        void update();
};

}

#endif