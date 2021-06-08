/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Box
*/

#ifndef BOX_HPP_
#define BOX_HPP_

#include "Cube.hpp"

class Box : public Cube
{
public:
    Box(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene);

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;

    rl::Texture *_txt;
    rl::Model *_model;
};

#endif /* !BOX_HPP_ */
