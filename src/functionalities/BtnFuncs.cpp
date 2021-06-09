/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** BtnFuncs
*/

#include "BtnFuncs.hpp"

void BF::playBtn(Bomberman *win, Btn *b)
{
    switchScene(win, 3);
}

void BF::optBtn(Bomberman *win, Btn *b)
{
    switchScene(win, 1);
}

void BF::backBtn(Bomberman *win, Btn *b)
{
    switchScene(win, 0);
}

void BF::quitBtn(Bomberman *win, Btn *b)
{
    win->_ending = true;
}

void BF::switchScene(Bomberman *win, int scene)
{
    win->_manager->_scene = scene;
}

void BF::repoLink(Bomberman *win, Btn *b)
{
    (void)win;
    #ifdef __linux__
        system("firefox https://github.com/EpitechIT2020/B-YEP-400-LIL-4-1-indiestudio-maxime.deroulou");
    #elif __APPLE__
        system("open \"https://github.com/EpitechIT2020/B-YEP-400-LIL-4-1-indiestudio-maxime.deroulou\"");
    #elif _WIN32
        system("explorer \"https://github.com/EpitechIT2020/B-YEP-400-LIL-4-1-indiestudio-maxime.deroulou\"");
    #else
        std::cerr << "Sorry ! This functionnality is not available on your OS!" << std::endl;
    #endif
}

void BF::fullScreen(Bomberman *win, Btn *b)
{
    if (win->_win->isFullscreen()) {
        b->_text = "Fullscreen: OFF";
        win->_win->setFullscreen();
    } else {
        b->_text = "Fullscreen: ON";
        win->_win->setFullscreen();
    }
}

/* Supported :
*   1920 x 1080
*   1600 x 900
*   1280 x 720
*   800  x 600
*/
void BF::resolutionBtn(Bomberman *win, Btn *b)
{
    const int widths[] = {800, 1280, 1600, 1920};
    const int heights[] = {600, 720, 900, 1080};
    const std::string texts[] = {" 800 x 600", " 1280 x 720", " 1600 x 900", " 1920 x 1080"};
    int cur = win->_win->getScreenWidth();
    int x = 0;

    for (auto w : widths) {
        if (w == cur)
            break;
        x++;
    }
    x = (x + 1) % 4;
    win->_win->setWindowSize(widths[x], heights[x]);
    b->_text = std::string("Resolution:") + texts[x];
}

void BF::skinBtn(Bomberman *win, Btn *b)
{
    switchScene(win, 5);
}