/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "../Object.hpp"

class Wall : public Cube
{
public:
    Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color, bool isWall, int scene);

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;

    rl::Texture *_texture;
    rl::Model *_model;
};

#endif /* !WALL_HPP_ */
