/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Ia
*/


#ifndef IA_HPP_
#define IA_HPP_

#include "../Object.hpp"
#include "../../raylib/rayLib.hpp"
#include <vector>


class PlayerAI : public Object3D
{
    public:
        PlayerAI(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::string pathText);
        PlayerAI(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models);

        void handleEvent() override {};
        void move(rl::Vec3 newPos) override {};
        void simulate() override {};
        void render(rl::Camera3d *cam) override {};

        std::shared_ptr<ByteObject> dump() override;

        std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> _models;
        std::shared_ptr<rl::Texture> _texture;

        rl::Vec3 _v = {0, 0, 0};
        rl::Vec3 _acc = {0, 0, 0};
        rl::Vec3 _direction = {0, 1, 0};
        rl::Vec3 _deadVec = {0, 0, 0};

        bool _isDead = false;
        float _scale;
        std::string _pathText;
        int _bombCount = 0;
        float _rotation = 0;
        float _frame = 0;
    private:
        void makeObj(std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models);
};

#endif