/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman Class
*/

#ifndef BOMB_CLASS_
#define BOMB_CLASS_

#include "entityComponent/Manager.hpp"
#include "Indie.hpp"

class ComponentManager;

class Bomberman
{
    public:
        Bomberman();
        ~Bomberman();

        void launch();
        void generateMap(int x, int y);
    private:
        ComponentManager *_manager;
        rl::Window *_win;
        rl::Font *_font;
};
#endif