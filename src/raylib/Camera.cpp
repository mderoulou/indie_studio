/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Camera funct
*/

#include "Camera.hpp"

/*
**  Camera 2d Functions
*/

rl::Camera2d::Camera2d()
    : ::Camera2D {0}
{
}

rl::Camera2d::Camera2d(rl::Vec2 offset,
                    rl::Vec2 target,
                    float rotation, 
                    float zoom)
    : ::Camera2D{offset, target, rotation, zoom}
{
}

/*
**  Camera 3d Functions
*/

rl::Camera3d::Camera3d()
    : ::Camera3D {0}
{
}

rl::Camera3d::Camera3d(rl::Vec3 pos,
                    rl::Vec3 target,
                    rl::Vec3 up,
                    float fovy,
                    int proj)
    : ::Camera3D{pos, target, up, fovy, proj}
{
}

void rl::Camera3d::update()
{
    UpdateCamera(this);
}