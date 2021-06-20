/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** EscManager
*/

#include "../Object.hpp"
#include "../../Indie.hpp"
#include "../../functionalities/BtnFuncs.hpp"
#include "raylib.h"

EscManager::EscManager(Bomberman *win, int scene)
{
    _scene = -1;
    _win = win;
}

void EscManager::handleEvent()
{
    int copy = _win->_manager->_settings._scene;
    void (*ptr[])(Bomberman *, Btn *, void *) = {0, &(BF::backBtn), &(BF::backBtn), &(BF::pauseBtn), &(BF::unpauseBtn), &(BF::backBtn), &(BF::backBtn), &(BF::backBtn)};

    if (rl::KeyBoard::IsKeyReleased(256) && copy != 0)
        (*ptr[copy])(_win, 0, 0);
}