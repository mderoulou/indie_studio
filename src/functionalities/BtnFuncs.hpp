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
    void playBtn(Bomberman *win, Btn *b, void *data);
    void repoLink(Bomberman *win, Btn *b, void *data);
    void optBtn(Bomberman *win, Btn *b, void *data);
    void quitBtn(Bomberman *win, Btn *b, void *data);
    void backBtn(Bomberman *win, Btn *b, void *data);
    void fullScreen(Bomberman *win, Btn *b, void *data);
    void resolutionBtn(Bomberman *win, Btn *b, void *data);
    void skinBtn(Bomberman *win, Btn *b, void *data);
    void addSkin(Bomberman *win, Btn *b, void *data);
    void removeSkin(Bomberman *win, Btn *b, void *data);
    void loadSkin(Bomberman *win, Btn *b, void *data);
    void loadAll(Bomberman *win);
    void mapSize(Bomberman *win, Btn *b, void *data);
    void previewSkin(Bomberman *win, void *data, std::string str);
}

#endif /* !BTNFUNCS_HPP_ */
