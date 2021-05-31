/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman Class
*/

#ifndef BOMB_CLASS_
#define BOMB_CLASS_

#include "Indie.hpp"

class Bomberman
{
    public:
        Bomberman();
        ~Bomberman();

        void launch();
        void drawEntity() {};
    private:
        rl::Window *_win;
        rl::Camera3d *_cam;
        rl::Font *_font;

};

// To put in the entity manager :
//        std::vector<std::shared_ptr<IObject>> objs;
#endif