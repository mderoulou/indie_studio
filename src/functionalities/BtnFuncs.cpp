/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** BtnFuncs
*/

#include "BtnFuncs.hpp"

void BF::playBtn(Bomberman *win, Btn *b, void *data)
{
    (void)b;
    (void)data;
    switchScene(win, 3);
}

void BF::optBtn(Bomberman *win, Btn *b, void *data)
{
    (void)b;
    (void)data;
    switchScene(win, 1);
}

void BF::backBtn(Bomberman *win, Btn *b, void *data)
{
    (void)b;
    (void)data;
    switchScene(win, 0);
}

void BF::quitBtn(Bomberman *win, Btn *b, void *data)
{
    (void)b;
    (void)data;
    win->_ending = true;
}

void BF::switchScene(Bomberman *win, int scene)
{
    win->_manager->_settings._scene = scene;
}

void BF::repoLink(Bomberman *win, Btn *b, void *data)
{
    (void)win;
    (void)b;
    (void)data;
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

void BF::fullScreen(Bomberman *win, Btn *b, void *data)
{
    (void)data;
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
void BF::resolutionBtn(Bomberman *win, Btn *b, void *data)
{
    const int widths[] = {800, 1280, 1600, 1920};
    const int heights[] = {600, 720, 900, 1080};
    const std::string texts[] = {" 800 x 600", " 1280 x 720", " 1600 x 900", " 1920 x 1080"};
    int cur = win->_win->getScreenWidth();
    int x = 0;

    (void)data;
    for (auto w : widths) {
        if (w == cur)
            break;
        x++;
    }
    x = (x + 1) % 4;
    win->_win->setWindowSize(widths[x], heights[x]);
    b->_text = std::string("Resolution:") + texts[x];
    for (auto obj : win->_manager->_objs) {
        if (Btn *b = dynamic_cast<Btn *>(obj))
            b->move(rl::Vec3(0.0, 0.0, 0.0));
        if (Input *b = dynamic_cast<Input *>(obj))
            b->move(rl::Vec3(0.0, 0.0, 0.0));
    }
}

void BF::skinBtn(Bomberman *win, Btn *b, void *data)
{
    (void)b;
    (void)data;
    switchScene(win, 5);
}

void BF::addSkin(Bomberman *win, Btn *b, void *data)
{
    std::ostringstream cmd("");

    (void)b;
    (void)data;
    if (!win->_manager->_settings._optSkin.size())
        return;
    if (win->_manager->_settings._skins.size() > 10) {
        std::cerr << "Skin limit reached !" << std::endl;
        return;
    }
    cmd << "curl https://minecraft.tools/download-skin/" << win->_manager->_settings._optSkin << " -o ../assets/skins/" << win->_manager->_settings._optSkin << ".png";
    #ifdef __linux__
        system(cmd.str().c_str());
    #elif _WIN32
        system(cmd.str().c_str());
    #else
        std::cerr << "Sorry ! This functionnality is not available on your OS!" << std::endl;
        return;
    #endif
    win->_manager->_settings._skins.push_back(std::string(win->_manager->_settings._optSkin) + ".png");
}

void BF::removeSkin(Bomberman *win, Btn *b, void *data)
{
    std::ostringstream cmd("");
    uint32_t pos = 0;

    (void)b;
    (void)data;
    cmd << "../assets/skins/" << win->_manager->_settings._optSkin << ".png";
    if (std::remove(cmd.str().c_str()) != 0) {
        std::cerr << "Unable to remove file ! Does it exists really ?" << std::endl;
        return;
    }
    for (auto str : win->_manager->_settings._skins) {
        if (str == win->_manager->_settings._optSkin)
            break;
        pos++;
    }
    for (auto ptr = win->_manager->_settings._skins.begin(); ptr < win->_manager->_settings._skins.end(); ptr++)
        if (*ptr == std::string(win->_manager->_settings._optSkin) + ".png")
            win->_manager->_settings._skins.erase(ptr);
}

void BF::loadSkin(Bomberman *win, Btn *b, void *data)
{
    Preview *ptr = (Preview *)data;
    std::ostringstream cmd("");

    (void)b;
    (void)data;
    if (!win->_manager->_settings._optSkin.size())
        return;
    cmd << "curl https://minecraft.tools/download-skin/" << win->_manager->_settings._optSkin << " -o ../assets/preview.png";
    #ifdef __linux__
        system(cmd.str().c_str());
    #elif _WIN32
        system(cmd.str().c_str());
    #else
        std::cerr << "Sorry ! This functionnality is not available on your OS!" << std::endl;
        return;
    #endif
    ptr->setTexture("../assets/preview.png");
}

void BF::loadAll(Bomberman *win)
{
    DIR *dir;
    struct dirent *ent;

    if (!(dir = opendir("../assets/skins/"))) {
        std::cerr << "Unable to open folder assets/skins !" << std::endl;
        return;
    }
    while ((ent = readdir(dir)) && win->_manager->_settings._skins.size() <= 10)
        if (ent->d_name[0] != '.')
            win->_manager->_settings._skins.push_back(std::string(ent->d_name));
    closedir(dir);
}

void BF::mapSize(Bomberman *win, Btn *b, void *data)
{
    const std::string sizes[] = {"Small", "Medium", "Large"};

    (void)data;
    win->_manager->_settings._sizeMap++;
    win->_manager->_settings._sizeMap %= 3;
    b->_text = std::string("Map size: ") + sizes[win->_manager->_settings._sizeMap];
}

void BF::previewSkin(Bomberman *win, void *data, std::string str)
{
    Preview *ptr = (Preview *)data;

    (void)win;
    ptr->setTexture(std::string(std::string("../assets/skins/") + str) + ".png");
}