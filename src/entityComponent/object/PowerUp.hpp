/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "../Object.hpp"

class PowerUp : public Cube
{
public:
    PowerUp(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture);
    PowerUp(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Texture> texture);
    ~PowerUp();

    void handleEvent() override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;
    std::shared_ptr<ByteObject> dump() override;
    bool explode(Bomb *) override;

    std::shared_ptr<rl::Texture> _texture;
    std::shared_ptr<rl::Model> _model;
private:
    void makeObj(std::shared_ptr<rl::Texture> texture);
};

#endif /* !POWERUP_HPP_ */
