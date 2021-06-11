/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman functions
*/

#include "Bomberman.hpp"

/* * * * * * * * * * * *\
*                       *
*      SCENES LIST      *
*\_____________________/*
*                       *
*   0 => MAIN MENU      *
*   1 => OPTIONS        *
*   2 => GAME LOBBY     *
*   3 => GAME           *
*   4 => PAUSE          *
*   5 => SKIN MENU      *
*                       *
\***********************/

Bomberman::Bomberman()
{
    std::srand(time(NULL));
    _win = new rl::Window(800, 600, "Indie Studio");
    _manager = new ComponentManager();

    preLoad();
    Player *player = new Player(rl::Vec3(1.0f, 0.0f, 1.0f), 0.4f, rl::Color(255, 255, 255, 255), 3, true, _t._walking);
    _manager->addComponent(player);
    // USED BY OTHERS :
    MusicManager *musicManager = new MusicManager(this);
    // HOME MENU :
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), "Play", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 0, this, &(BF::playBtn), (void *)musicManager, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 60.0), "Skins", 24,  rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 0, this, &(BF::skinBtn), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(104.0, 120.0), "Respository", 24,  rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 0, this, &(BF::repoLink), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-100.0, 120.0), "Options", 24, rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 0, this, &(BF::optBtn), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 180.0), "Quit Game", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 0, this, &(BF::quitBtn), 0, _t._btn, _t._ft));
    // OPTIONS MENU :
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), "FullScreen: OFF", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::fullScreen), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 60.0), "Resolution: 800 x 600", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::resolutionBtn), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 120.0), "Map size: Small", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::mapSize), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::backBtn), 0, _t._btn, _t._ft));
    // SKINS MENU :
    Preview *preview = new Preview(rl::Color(255, 255, 255, 255), _t._walking);
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(-340.0, 0.0), "+", 24, rl::Rectangle(596,0,40,40), "../assets/musics/click.wav", 5, this, &(BF::addSkin), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(-290.0, 0.0), "-", 24, rl::Rectangle(596,0,40,40), "../assets/musics/click.wav", 5, this, &(BF::removeSkin), 0, _t._btn, _t._ft));
    _manager->addComponent(new Input(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(-50.0, 0.0), _manager->_settings._optSkin, 16, 5, 24, this, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(270.0, 0.0), "Load Preview", 24, rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 5, this, &(BF::loadSkin), (void *)preview, _t._btn, _t._ft));
    _manager->addComponent(preview);
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 5, this, &(BF::backBtn), 0, _t._btn, _t._ft));
    _manager->addComponent(new List(rl::Vec2(1.0/2, 7.0/20), rl::Vec2(-350, 0.0), rl::Vec2(0.0, 35.0), 24, 5, this, &(_manager->_settings._skins), &(BF::previewSkin), preview, _t._ft, true, 4));
    //GAME LOBBY :
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(104.0, 0.0), "Fight", 24,  rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 2, this, &(BF::launchGame), 0, _t._btn, _t._ft));
    _manager->addComponent(new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(-100.0, 0.0), "Back", 24, rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 2, this, &(BF::backBtn), 0, _t._btn, _t._ft));
    // ALL MENUS :
    _manager->addComponent(musicManager);
    //Background *bg = new Background(rl::Vec3(1.0f, -23.0f, -2.0f), 3);
    //_manager->addComponent(bg);
    generateMap(medium);
    _win->changeFps(60);
}

Bomberman::~Bomberman()
{
    rl::Sound::CloseAudioDevice();
    delete _win;
    delete _manager;
}

void Bomberman::generateMap(mapSize type)
{
    int x = type;
    int y = type;

    _manager->_cam->setTarget(rl::Vec3(x / 2,  0, y / 2));
    _manager->_cam->moveCamera(rl::Vec3(x / 2,  0, y / 2) + rl::Vec3(0, x * 1.3, y));

    // Create the ground
    for (int i = 0; i < x; i += 1) {
        for (int j = 0; j < y; j += 1) {
            _manager->addComponent(new Wall(rl::Vec3(i, -1.0f, j),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, _t._sb));
        }
    }

    // Create the border X
    for (int i = 0; i < x; i += 1) {
        _manager->addComponent(new Wall(rl::Vec3(i, 0.0f, 0.0f),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, _t._sb));
        _manager->addComponent(new Wall(rl::Vec3(i, 0.0f, y),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, _t._sb));
    }

    // Create the border Y
    for (int i = 1; i < y; i += 1) {
        _manager->addComponent(new Wall(rl::Vec3(0.0f, 0.0f, i),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, _t._sb));
        _manager->addComponent(new Wall(rl::Vec3(x - 1, 0.0f, i),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, _t._sb));
    }
}

void Bomberman::launch()
{
    while (!_win->ShouldClose() && !_ending) {
        _win->clearBackground(rl::Color(255, 255, 255, 255));
        _win->beginDrawing();

        _t._ft->drawFPS(5, 25);
        _manager->handleEvent();
        _manager->simulate();
        _manager->renderAll();
        _win->endDrawing();
    }
}

void Bomberman::preLoad()
{
    BF::loadAll(this); //Load all available skins;
    rl::Sound::InitAudioDevice(); // Init audio
    if (!rl::Sound::IsAudioDeviceReady())
        throw "Unable to load Audio Device!";

    _t._btn = std::make_shared<rl::Texture>("../assets/menus/btns.png");
    _t._sb = std::make_shared<rl::Texture>("../assets/block/stone-bricks.png");
    _t._tnt_a = std::make_shared<rl::Model>("../assets/block/tnt.glb");
    _t._ft = std::make_shared<rl::Font>("../assets/minecraftia.ttf");
    _t._walking = std::make_shared<std::vector<std::shared_ptr<rl::Model>>>();
    std::ostringstream objPath("");

    for (int i = 1; i < 41; i++) {
        if (i < 10)
            objPath << "../assets/steve-obj/anims/steve_0" << i << ".glb";
        else
            objPath << "../assets/steve-obj/anims/steve_" << i << ".glb";
        _t._walking->push_back(std::make_shared<rl::Model>(objPath.str().c_str()));
        objPath.str("");
        objPath.clear();
    }
}