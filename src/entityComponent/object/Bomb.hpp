/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "../Object.hpp"
#include "../../raylib/rayLib.hpp"
#include <vector>

class Bomb : public Object3D
{
public:
    Bomb(rl::Vec3 pos, float scale, rl::Color color, int scene, float time);

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;

    rl::Model *_model;
    rl::Texture *_texture;
    float _scale;
    int _time;
    bool _explosed;
    float _rotation = 0;
private:
};

#endif