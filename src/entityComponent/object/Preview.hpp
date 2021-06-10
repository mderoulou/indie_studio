/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Preview
*/

#ifndef PREVIEW_HPP_
#define PREVIEW_HPP_

#include "../Object.hpp"
#include "../Manager.hpp"

class Preview : public Object3D
{
public:
    Preview(rl::Color color);
    ~Preview();

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;

    std::vector<rl::Model *> _models;
    rl::Texture *_texture;

    float _scale;
    float _rotation;
    float _frame = 0;
    void setTexture(const std::string filename);
private:
    void loadAnims();
};

#endif