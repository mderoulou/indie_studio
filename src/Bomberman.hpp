/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman Class
*/

#ifndef BOMB_CLASS_
#define BOMB_CLASS_

#include "entityComponent/Manager.hpp"
#include "functionalities/BtnFuncs.hpp"
#include "Indie.hpp"

#include <memory>

class ComponentManager;

enum mapSize { small = 11, medium = 17, large = 21};

class allTexture
{
    public:
        std::shared_ptr<rl::Texture> _btn; // Btn texture
        std::shared_ptr<rl::Texture> _sb; // StoneBrick texture
        std::shared_ptr<rl::Texture> _wood; // wood texture
        std::shared_ptr<rl::Font> _ft; // Minecraft font
        std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> _walking; // Walking Animation
        std::shared_ptr<rl::Model> _tnt_a;
};

class Bomberman
{
    public:
        Bomberman();
        ~Bomberman();

        void launch();
        void generateMap(mapSize type);
        ComponentManager *_manager;
        allTexture _t;
        rl::Window *_win;
        bool _ending = false;
    private:
        void preLoad();
};
#endif