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
    Wall(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture);
    Wall(std::shared_ptr<ByteObject> &obj, std::shared_ptr<rl::Texture> texture);

    void handleEvent() override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;
    std::shared_ptr<ByteObject> dump() override;
    virtual bool explode(Bomb *) override;

    std::shared_ptr<rl::Texture> _texture;
    std::shared_ptr<rl::Model> _model;
private:
    void makeObj(std::shared_ptr<rl::Texture> texture);
};

#endif /* !WALL_HPP_ */
