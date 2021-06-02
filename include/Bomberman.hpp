/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman Class
*/

#ifndef BOMB_CLASS_
#define BOMB_CLASS_

#include "Manager.hpp"
#include "Indie.hpp"

class ComponentManager;

class Bomberman
{
    public:
        Bomberman();
        ~Bomberman();

        void launch();
    private:
        ComponentManager *_manager;
        rl::Window *_win;
        rl::Camera3d *_cam;
        rl::Font *_font;

};

#endif