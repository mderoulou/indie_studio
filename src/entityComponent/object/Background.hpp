/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Background
*/

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include "../Object.hpp"

class Background : public Object3D
{
    public:
        Background(rl::Vec3 pos, int scene);

        void render(rl::Camera3d *cam) override;
    private:

        rl::Texture *_texture;
        rl::Model *_model;
        rl::Vec3 _pos;
        rl::Color _color;
        float _scale;

};

#endif