/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "../Object.hpp"

class PowerUp : public Object3D {
public:
    PowerUp(rl::Vec3 pos, std::shared_ptr<rl::Model> model, int scene, float scale = 0.4, rl::Color color = {255, 255, 255, 255});
    PowerUp(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model);
    ~PowerUp();

    void handleEvent() override {};
    void render(rl::Camera3d *cam) override;
    std::shared_ptr<ByteObject> dump() override;

    virtual void apllyToPlayer(Player *p);
    void simulate() override;

    static std::shared_ptr<PowerUp> factory(std::shared_ptr<ByteObject> &obj, Bomberman *b);

    float _scale;
    float _rotation = 0;

    enum type {
        BOMBCOUNT,
        BOMBPOWER,
        SPEED,
    };

    std::shared_ptr<rl::Model> _model;
private:
    void makeObj(std::shared_ptr<rl::Model> model);
};

class PowerBombsCount : public PowerUp {
public:
    PowerBombsCount(rl::Vec3 pos, int scene, std::shared_ptr<rl::Model> model);
    PowerBombsCount(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model);

    std::shared_ptr<ByteObject> dump() override;

    void apllyToPlayer(Player *p) override;

};

class PowerBombsPower : public PowerUp {
public:
    PowerBombsPower(rl::Vec3 pos, int scene, std::shared_ptr<rl::Model> model);
    PowerBombsPower(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model);

    std::shared_ptr<ByteObject> dump() override;

    void apllyToPlayer(Player *p) override;

};

class PowerSpeed : public PowerUp {
public:
    PowerSpeed(rl::Vec3 pos, int scene, std::shared_ptr<rl::Model> model);
    PowerSpeed(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Model> model);

    std::shared_ptr<ByteObject> dump() override;

    void apllyToPlayer(Player *p) override;

};

#endif /* !POWERUP_HPP_ */
