/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Skybox
*/

#ifndef SKYBOX_HPP_
#define SKYBOX_HPP_

#include "../Object.hpp"

class Skybox : public Object3D
{
public:
    Skybox(Bomberman *win);

    void handleEvent() override {};
    void move(rl::Vec3 move) override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;

    std::shared_ptr<rl::Mesh> _mesh;
    std::shared_ptr<rl::Model> _skybox;
    std::shared_ptr<rl::Shader> _shader;
private:
    Bomberman *_m;
};

#endif
