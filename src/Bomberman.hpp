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

class Bomberman
{
    public:
        Bomberman();
        ~Bomberman();

        void launch();
        void generateMap(int x, int y);
        ComponentManager *_manager;
        rl::Window *_win;
    private:
        rl::Font *_font;
};
#endif