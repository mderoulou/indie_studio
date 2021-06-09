/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../Object.hpp"
#include "../../raylib/rayLib.hpp"
#include <vector>

class Player : public Object3D
{
public:
    Player(rl::Vec3 pos, float scale, rl::Color color, std::string pathText, int scene, bool _isKeyboad); // load Specific texture
    Player(rl::Vec3 pos, float scale, rl::Color color, int scene, bool _isKeyboad); // steve specific texture
    ~Player();

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;

    std::vector<rl::Model *> _models;
    rl::Texture *_texture;
    rl::ModelAnimation *_anim;

    rl::Vec3 _v = {0, 0, 0};
    rl::Vec3 _acc = {0, 0, 0};


    float _scale;
    float _rotation = 0;
    float _frame = 0;
    Control *_controller = 0;
private:
    void loadAnims();
};


#endif /* !PLAYER_HPP_ */
