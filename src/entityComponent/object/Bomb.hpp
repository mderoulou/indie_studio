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
    Bomb(rl::Vec3 pos, float scale, rl::Color color, int scene, float time, std::shared_ptr<rl::Model> model, Player *player, int explosionRadius);
    ~Bomb();

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;
    virtual bool explode(Bomb *) override;

    std::shared_ptr<rl::Model> _model;
    Player *_player;
    float _scale;
    int _time;
    int _maxTime;
    bool _explosed;
    int _explosionRadius;
    float _rotation = 0;
    rl::Vec3 _v = {0, 0, 0};
    rl::Vec3 _acc = {0, 0, 0};
private:
};

#endif