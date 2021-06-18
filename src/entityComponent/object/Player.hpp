/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../Object.hpp"
#include "../../functionalities/Control.hpp"
#include "../../raylib/rayLib.hpp"
#include <vector>

class Bomb;

class Player : public Object3D
{
public:
    Player(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<Controls> controls, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, const std::string path = "assets/skins/skin.png");
    Player(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::shared_ptr<Controls> controls);

    virtual void handleEvent() override;
    void move(rl::Vec3 newPos) override;
    virtual void simulate() override;
    void render(rl::Camera3d *cam) override;
    bool explode(Bomb *) override;
    void die();
    void physiX(float acc_mult, bool hasMove);
    std::shared_ptr<ByteObject> dump() override;

    std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> _models;
    std::shared_ptr<rl::Texture> _texture;

    rl::Vec3 _v = {0, 0, 0};
    rl::Vec3 _acc = {0, 0, 0};
    rl::Vec3 _direction = {0, 1, 0};
    rl::Vec3 _deadVec = {0, 0, 0};

    uint _playerId = -1;
    bool _isKeyboard = true;
    bool _isKeyUsed = false;
    bool _isDead = false;
    int _deathTime = 300;
    int _explosionRadius = 1;
    float _scale;
    std::string _pathText;
    int _maxBombCount = 1;
    int _bombCount = 0;
    float _rotation = 0;
    float _frame = 0;
    uint16_t _cId;
    std::shared_ptr<Controls> _controller = 0;
    float _speedFactor = 0.8;
private:
    void makeObj(std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models);
};


#endif /* !PLAYER_HPP_ */
