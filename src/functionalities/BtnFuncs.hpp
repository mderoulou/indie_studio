/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** BtnFuncs
*/

#ifndef BTNFUNCS_HPP_
#define BTNFUNCS_HPP_

#include <filesystem>
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
    void launchGame(Bomberman *win, Btn *b, void *data);
    void setMusic(Bomberman *win, Slider *s, void *data);
    void setSound(Bomberman *win, Slider *s, void *data);
    void switchType(Bomberman *win, Btn *b, void *data);
    void switchSkin(Bomberman *win, Btn *b, void *data);
    void pauseBtn(Bomberman *win, Btn *b, void *data);
    void unpauseBtn(Bomberman *win, Btn *b, void *data);
    void saveBtn(Bomberman *win, Btn *b, void *data);
    void homeBtn(Bomberman *win, Btn *b, void *data);
    void saveSettings(Bomberman *win, Btn *b, void *data);
    void loadGame(Bomberman *win, Btn *b, void *data);
    void helpBtn(Bomberman *win, Btn *b, void *data);
    void leaveHelp(Bomberman *win, Btn *b, void *data);
}

#endif /* !BTNFUNCS_HPP_ */
