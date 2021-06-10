/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Box
*/

#ifndef BOX_HPP_
#define BOX_HPP_

#include "../Object.hpp"

class Box : public Cube
{
public:
    Box(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene);

    void render(rl::Camera3d *cam) override;

    rl::Texture *_texture;
    rl::Model *_model;
    float _rotation;
    float _scale;
};

#endif /* !BOX_HPP_ */
