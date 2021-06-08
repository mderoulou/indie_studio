/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** BtnFuncs
*/

#include "BtnFuncs.hpp"

void BF::playBtn(Bomberman *win)
{
    switchScene(win, 3);
}

void BF::switchScene(Bomberman *win, int scene)
{
    win->_manager->_scene = scene;
}