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
#include <algorithm>

class PlayerAI : public Player
{
    public:
        PlayerAI(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<Controls> controls, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::string pathText);
        PlayerAI(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::shared_ptr<Controls> controls);

        static std::shared_ptr<PlayerAI> factory(std::shared_ptr<ByteObject> &obj, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models);
        static std::shared_ptr<PlayerAI> factory(rl::Vec3 pos, float scale, rl::Color color, int scene, std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> models, std::string pathText);

        std::shared_ptr<ByteObject> dump() override;
    private:
};

class ControlsAI : public Controls {
    public:
        ControlsAI();
        void setPlayer(std::shared_ptr<PlayerAI> player);
        void simulate();

        float isKeyUp() override;
        float isKeyDown() override;
        float isKeyLeft() override;
        float isKeyRight() override;
        int isKeyUse() override;
        int isKeyOther() override {return 0;};


        std::shared_ptr<PlayerAI> _player;
        uint _frame = 0;
        rl::Vec3 _axis = {0, 0, 0};
        bool _use = false;

        enum cellType {
            EMPTY = 0,
            BLOCKING = 1,
            BLOCKEXPLOSION = 128,
            BOX = 4 | BLOCKING | BLOCKEXPLOSION,
            WALL = 8 | BLOCKING | BLOCKEXPLOSION,
            BOMB = 16 | BLOCKING,
            PLAYER = 32,
            POWERUP = 64,
            WILLDIE = 256,
            WILLDIESOON = 1024,
            WILLDAMGE = 512,
        };

    private:

};

#endif