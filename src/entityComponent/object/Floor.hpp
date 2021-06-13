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
    Floor(std::shared_ptr<ByteObject> obj, std::shared_ptr<rl::Texture> texture);
    ~Floor();

    void handleEvent() override {};
    void simulate() override {};
    void render(rl::Camera3d *cam) override;
    std::shared_ptr<ByteObject> dump() override;

    std::shared_ptr<rl::Texture> _texture;
    std::shared_ptr<rl::Model> _model;
private:
    void makeObj(std::shared_ptr<rl::Texture> texture);
};

#endif /* !FLOOR_HPP_ */
