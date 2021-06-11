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

class ComponentManager;

enum mapSize { small = 10, medium = 16, large = 20};

class allTexture
{
    public:
        rl::Texture *_btn; // Btn texture
        rl::Texture *_sb; // StoneBrick texture
        rl::Font *_ft; // Minecraft font
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
        rl::Font *_font;
};
#endif