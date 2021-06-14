/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Particle
*/

#ifndef Particle_HPP_
#define Particle_HPP_

#include "../Object.hpp"

class Particle : public Cube
{
public:
    Particle(rl::Vec3 pos, rl::Vec3 size, rl::Color color, int scene, std::shared_ptr<rl::Texture> texture, int life);
    Particle(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<rl::Model> model, int life);
    ~Particle();

    void simulate() override;
    void render(rl::Camera3d *cam) override;
    bool explode(Bomb *) override;
    void handleEvent() override {};
    void makeObj(std::shared_ptr<rl::Texture> texture, int life);

    std::shared_ptr<rl::Texture> _texture;
    std::shared_ptr<rl::Model> _model;
    rl::Vec3 _v = {0, 0, 0};
    rl::Vec3 _acc = {0, 0, 0};
    int _life = 60;
    float _rotation = 0;
    float _scale = 1;
private:
    void makeObj(std::shared_ptr<rl::Texture> texture);
};

#endif /* !Particle_HPP_ */
