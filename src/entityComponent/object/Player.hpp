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
    Player(rl::Vec3 pos, float scale, rl::Color color, const std::string &path, int scene, bool _isKeyboad, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models); // load Specific texture
    Player(rl::Vec3 pos, float scale, rl::Color color, int scene, bool _isKeyboad, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models); // steve specific texture

    void handleEvent() override;
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;

    std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> _models;
    std::shared_ptr<rl::Texture> _texture;
    rl::ModelAnimation *_anim;

    rl::Vec3 _v = {0, 0, 0};
    rl::Vec3 _acc = {0, 0, 0};

    bool _isKeyUsed = false;
    float _scale;
    int _bombCount = 0;
    float _rotation = 0;
    float _frame = 0;
    Control *_controller = 0;
};


#endif /* !PLAYER_HPP_ */
