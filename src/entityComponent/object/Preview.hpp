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
#include "../../raylib/rayLib.hpp"

class Preview : public Object3D
{
public:
    Preview(rl::Vec3 pos, float scale, int scene, float rotation, rl::Color color, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models);

    void handleEvent() override {};
    void move(rl::Vec3 newPos) override;
    void simulate() override;
    void render(rl::Camera3d *cam) override;

    std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> _models;
    std::shared_ptr<rl::Texture> _texture;

    float _scale;
    float _rotation;
    float _frame = 0;
    void setTexture(const std::string filename);
    bool _disabled;
private:
    void loadAnims();
};

#endif