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

void BF::optBtn(Bomberman *win)
{
    switchScene(win, 1);
}

void BF::quitBtn(Bomberman *win)
{

}

void BF::switchScene(Bomberman *win, int scene)
{
    win->_manager->_scene = scene;
}

void BF::repoLink(Bomberman *win)
{
    (void)win;
    rl::Ray::openUrl("https://github.com/EpitechIT2020/B-YEP-400-LIL-4-1-indiestudio-maxime.deroulou");
}