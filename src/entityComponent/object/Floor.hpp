/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Wall
*/

#ifndef FLOOR_HPP_
#define FLOOR_HPP_

#include "../Object.hpp"

class Floor : public Cube
{
public:
    Floor(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture);
    ~Floor();

    void handleEvent() override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;

    std::shared_ptr<rl::Texture> _texture;
    std::shared_ptr<rl::Model> _model;
};

#endif /* !FLOOR_HPP_ */
