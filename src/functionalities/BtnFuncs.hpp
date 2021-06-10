/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** BtnFuncs
*/

#ifndef BTNFUNCS_HPP_
#define BTNFUNCS_HPP_

#include <sys/types.h>
#include <dirent.h>
#include <sstream>
#include "../Bomberman.hpp"

namespace BF {
    void switchScene(Bomberman *win, int scene);
    void playBtn(Bomberman *win, Btn *b);
    void repoLink(Bomberman *win, Btn *b);
    void optBtn(Bomberman *win, Btn *b);
    void quitBtn(Bomberman *win, Btn *b);
    void backBtn(Bomberman *win, Btn *b);
    void fullScreen(Bomberman *win, Btn *b);
    void resolutionBtn(Bomberman *win, Btn *b);
    void skinBtn(Bomberman *win, Btn *b);
    void addSkin(Bomberman *win, Btn *b);
    void removeSkin(Bomberman *win, Btn *b);
    void loadSkin(Bomberman *win, Btn *b);
    void loadAll(Bomberman *win);
    void mapSize(Bomberman *win, Btn *b);
}

#endif /* !BTNFUNCS_HPP_ */
