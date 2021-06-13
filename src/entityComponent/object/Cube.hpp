/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Cube
*/

#ifndef CUBE_HPP_
#define CUBE_HPP_

#include "../Object.hpp"

class Cube : public Object3D
{
public:
    Cube() {};
    Cube(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene);

    void render(rl::Camera3d *cam) override;

    rl::Vec3 _size;
    bool _isBreakable;
};
#endif /* !CUBE_HPP_ */
