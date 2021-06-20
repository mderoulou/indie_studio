/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** BtnFuncs
*/

#include "BtnFuncs.hpp"

void BF::playBtn(Bomberman *win, Btn *b, void *data)
{
    MusicManager *mm = (MusicManager *)data;
    (void)b;
    switchScene(win, 2);
    mm->playSound("prepare_yourself.ogg", false);
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

void BF::pauseBtn(Bomberman *win, Btn *b, void *data)
{
    (void)b;
    (void)data;
    rl::Mouse::ShowCursor();
    switchScene(win, 4);
}

void BF::unpauseBtn(Bomberman *win, Btn *b, void *data)
{
    (void)b;
    (void)data;
    rl::Mouse::HideCursor();
    switchScene(win, 3);
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
    int ret = 0;

    (void)win;
    (void)b;
    (void)data;
    #ifdef __linux__
        ret = system("firefox https://github.com/EpitechIT2020/B-YEP-400-LIL-4-1-indiestudio-maxime.deroulou");
        (void)ret;
    #elif __APPLE__
        ret = system("open \"https://github.com/EpitechIT2020/B-YEP-400-LIL-4-1-indiestudio-maxime.deroulou\"");
        (void)ret;
    #elif _WIN32
        ret = system("explorer \"https://github.com/EpitechIT2020/B-YEP-400-LIL-4-1-indiestudio-maxime.deroulou\"");
        (void)ret;
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
        win->_manager->_settings._fScreen = false;
    } else {
        b->_text = "Fullscreen: ON";
        win->_win->setFullscreen();
        win->_manager->_settings._fScreen = true;
    }
    win->_win->setWindowSize(win->_manager->_settings._width, win->_manager->_settings._height);
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
    win->_manager->_settings._width = widths[x];
    win->_manager->_settings._height = heights[x];
    b->_text = std::string("Resolution:") + texts[x];
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
    GameOpt *opts = (GameOpt *)data;
    int ret = 0;

    (void)b;
    (void)data;
    if (!win->_manager->_settings._optSkin.size())
        return;
    if (win->_manager->_settings._skins.size() > 10) {
        std::cerr << "Skin limit reached !" << std::endl;
        return;
    }
    cmd << "curl https://minecraft.tools/download-skin/" << win->_manager->_settings._optSkin << " -o assets/skins/" << win->_manager->_settings._optSkin << ".png";
    #ifdef __linux__
        ret = system(cmd.str().c_str());
        (void)ret;
    #elif _WIN32
        ret = system(cmd.str().c_str());
        (void)ret;
    #elif __APPLE__
        ret = system(cmd.str().c_str());
        (void)ret;
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
    GameOpt *opts = (GameOpt *)data;

    (void)b;
    (void)data;
    cmd << "assets/skins/" << win->_manager->_settings._optSkin << ".png";
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
    int ret = 0;

    (void)b;
    (void)data;
    if (!win->_manager->_settings._optSkin.size())
        return;
    cmd << "curl https://minecraft.tools/download-skin/" << win->_manager->_settings._optSkin << " -o assets/preview.png";
    #ifdef __linux__
        ret = system(cmd.str().c_str());
        (void)ret;
    #elif _WIN32
        ret = system(cmd.str().c_str());
        (void)ret;
    #elif __APPLE__
        ret = system(cmd.str().c_str());
        (void)ret;
    #else
        std::cerr << "Sorry ! This functionnality is not available on your OS!" << std::endl;
        return;
    #endif
    ptr->setTexture("assets/preview.png");
}

void BF::loadAll(Bomberman *win)
{
    for (const auto &entry : std::filesystem::directory_iterator("assets/skins/"))
        if (win->_manager->_settings._skins.size() <= 10 && entry.path().filename().string()[0] != '.')
            win->_manager->_settings._skins.push_back(std::string(entry.path().filename().string().c_str()));
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
    ptr->setTexture(std::string(std::string("assets/skins/") + str) + ".png");
}


void runGraphique(Bomberman* bomberman) {
    bomberman->_win->beginDrawing();
    ClearBackground(Color{255, 255, 255, 255});
    bomberman->_win->clearBackground(rl::Color(255, 255, 255, 255));
    bomberman->_skybox->render(bomberman->_manager->_cam);
    bomberman->_t._ft->drawFPS(5, 25);
    bomberman->_manager->manageCamera();
    bomberman->_manager->renderAll();
    bomberman->_win->endDrawing();

}

void countDown(Bomberman* win)
{
    win->_manager->_mm->playSound("3.ogg", false);
    for (int i = 0; i < 60; i++)
        runGraphique(win);
    win->_manager->_mm->playSound("2.ogg", false);
    for (int i = 0; i < 60; i++)
        runGraphique(win);
    win->_manager->_mm->playSound("1.ogg", false);
    for (int i = 0; i < 60; i++)
        runGraphique(win);
    win->_manager->_mm->playSound("fight.ogg", false);
}

void BF::launchGame(Bomberman *win, Btn *b, void *data)
{
    int count = 0;
    GameOpt *go = (GameOpt *)data;
    for (auto types : go->_types) {
        if (types)
            count++;
    }
    if (count >= 2) {
        int size = 11 + 6 * win->_manager->_settings._sizeMap;
        rl::Vec3 spawnPoints[] = {
            {(float)1  , 0, (float)1},
            {(float)(size-2), 0, (float)(size-2)},
            {(float)1  , 0, (float)(size-2)},
            {(float)(size-2), 0, (float)1},
        };
        win->generateMap(size);
        switchScene(win, 3);
        for (int i = 0; i < 4; i++) {
            if (!go->_types[i])
                continue;
            if (go->_types[i] == 2) { // AI
                std::shared_ptr<PlayerAI> player = PlayerAI::factory(spawnPoints[i], 0.4f, rl::Color(255, 255, 255, 255), 3, win->_t._walking, std::string("assets/skins/") + go->_names[i]);
                player->_playerId = i;
                win->_manager->addComponent(player, 3);
            } else { // PLAYER
                std::shared_ptr<Player> player = std::make_shared<Player>(spawnPoints[i], 0.4f, rl::Color(255, 255, 255, 255), 3, go->_controllers[i], win->_t._walking, std::string("assets/skins/") + go->_names[i]);
                player->_playerId = i;
                win->_manager->addComponent(player, 3);
            }
        }
        countDown(win);
        rl::Mouse::HideCursor();
    }
}

void BF::setMusic(Bomberman *win, Slider *s, void *data)
{
 
    float vol = s->_cpos.x * 1.0534;

    (void)data;
    win->_manager->_settings._mVol = vol;
    s->_text = std::string(std::string("Musics: ") + std::to_string((int)(vol * 100)) + "%");
}

void BF::setSound(Bomberman *win, Slider *s, void *data)
{
    float vol = s->_cpos.x * 1.0534;

    (void)data;
    win->_manager->_settings._sVol = vol;
    s->_text = std::string(std::string("Sounds: ") + std::to_string((int)(vol * 100)) + "%");
}

void BF::switchType(Bomberman *win, Btn *b, void *data)
{
    static GameOpt *opts = 0;
    uint64_t index = (uint64_t)data;
    const std::string types[] = {"None", "IA"};

    if (!opts)
        for (auto obj : win->_manager->_objs[win->_manager->_settings._scene])
            if (GameOpt *t = dynamic_cast<GameOpt *>(obj.get()))
                opts = t;
    if (!opts->_types[index])
        opts->_types[index] = 2;
    else
        opts->_types[index] = 0;
    opts->_controllers[index] = 0;
    if (!opts->_types[index])
        opts->_previews[index]->_disabled = true;
    else
        opts->_previews[index]->_disabled = false;
    b->_text = opts->_types[index] ? "IA" : "None";
}

void BF::switchSkin(Bomberman *win, Btn *b, void *data)
{
    static GameOpt *opts = 0;
    uint64_t index = (uint64_t)data;
    uint64_t sindex = -1;

    if (!opts)
        for (auto obj : win->_manager->_objs[win->_manager->_settings._scene])
            if (GameOpt *t = dynamic_cast<GameOpt *>(obj.get()))
                opts = t;
    if (win->_manager->_settings._skins.size()) {
        for (int x = 0; x < win->_manager->_settings._skins.size(); x++)
            if (win->_manager->_settings._skins[x] == opts->_names[index]) {
                sindex = x;
                break;
            }
        if (sindex != -1) {
            std::cout << sindex << std::endl;
            opts->_names[index] = win->_manager->_settings._skins[(sindex + 1) % (win->_manager->_settings._skins.size())];
            opts->_previews[index]->setTexture(std::string("assets/skins/") + opts->_names[index]);
            b->_text = opts->_names[index].substr(0, opts->_names[index].size() - 4);
        } else {
            opts->_names[index] = win->_manager->_settings._skins[0];
            opts->_previews[index]->setTexture(std::string("assets/skins/") + opts->_names[index]);
            b->_text = opts->_names[index].substr(0, opts->_names[index].size() - 4);
        }
    } else {
        opts->_names[index] = "skin.png";
        opts->_previews[index]->setTexture(std::string("assets/skins/") + opts->_names[index]);
        b->_text = "skin";
    }
}

void BF::saveBtn(Bomberman *win, Btn *b, void *data)
{
    win->saveMap();
    switchScene(win, 0);
}

void BF::homeBtn(Bomberman *win, Btn *b, void *data)
{
    win->_manager->_objs[3].clear();
    switchScene(win, 0);
}

void BF::saveSettings(Bomberman *win, Btn *b, void *data)
{
    win->saveSettings();
    switchScene(win, 0);
}

void BF::loadGame(Bomberman *win, Btn *b, void *data)
{
    win->_manager->_objs[3].clear();
    if (!win->loadMap())
        return;
    switchScene(win, 3);
    countDown(win);
    rl::Mouse::HideCursor();
}

void BF::helpBtn(Bomberman *win, Btn *b, void *data)
{
    (void)data;
    (void)b;
    switchScene(win, 7);
}

void BF::leaveHelp(Bomberman *win, Btn *b, void *data)
{
    (void)data;
    (void)b;
    switchScene(win, 0);
}