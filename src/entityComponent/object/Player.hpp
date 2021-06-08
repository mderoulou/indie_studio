/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../Object.hpp"

class Player : public Object3D
{
public:
    Player(rl::Vec3 pos, float scale, rl::Color color, std::string pathText, int scene); // load Specific texture
    Player(rl::Vec3 pos, float scale, rl::Color color, int scene); // steve specific texture
    ~Player();

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;

    rl::Model *_model;
    rl::Texture *_texture;
    rl::ModelAnimation *_anim;
    float _scale;
    float _rotation;
    int _frame;
};


#endif /* !PLAYER_HPP_ */
