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
    : ::Camera2D {0, 0, 0, 0, 0, 0}
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
    : ::Camera3D {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
{
}

rl::Camera3d::Camera3d(rl::Vec3 pos,
                    rl::Vec3 target,
                    rl::Vec3 up,
                    float fovy,
                    int proj)
    : ::Camera3D{pos, target, up, fovy, proj}
{
    _isStarted = false;
}

void rl::Camera3d::update()
{
    UpdateCamera(this);
}

void rl::Camera3d::setCameraMode(int mode)
{
    SetCameraMode(*this, mode);
}

void rl::Camera3d::beginMode()
{
    if (_isStarted) {
        TraceLog(LOG_WARNING, "3d Camera already began.");
        return;
    }
    _isStarted = true;
    BeginMode3D(*this);
}

void rl::Camera3d::endMode()
{
    if (!_isStarted) {
        TraceLog(LOG_WARNING, "3d Camera already ended.");
        return;
    }
    _isStarted = false;
    EndMode3D();
}

void rl::Camera3d::moveCamera(rl::Vec3 newPos)
{
    this->position = newPos;
}

void rl::Camera3d::setTarget(rl::Vec3 newPos)
{
    this->target = newPos;
}

rl::Vec3 rl::Camera3d::getPosition()
{
    return (rl::Vec3(this->position));
}

rl::Vec3 rl::Camera3d::getTarget()
{
    return (rl::Vec3(this->target));
}