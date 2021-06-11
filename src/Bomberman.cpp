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
    rl::Sound::InitAudioDevice();
    if (!rl::Sound::IsAudioDeviceReady())
        throw "Unable to load Audio Device!";
    _font = new rl::Font();
    _manager = new ComponentManager();
    BF::loadAll(this);
    Player *player = new Player(rl::Vec3(1.0f, 0.0f, 1.0f), 0.4f, rl::Color(255, 255, 255, 255), 3, true);
    Preview *preview = new Preview(rl::Color(255, 255, 255, 255));
    MusicManager *mm = new MusicManager(this);
    this->_t._btn = new rl::Texture("../assets/menus/btns.png");
    this->_t._sb = new rl::Texture("../assets/block/stone-bricks.png");
    this->_t._ft = new rl::Font("../assets/minecraftia.ttf");
    Btn *p = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), "Play", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 0, this, &(BF::playBtn), (void *)mm, this->_t._btn, this->_t._ft);
    Btn *s = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 60.0), "Skins", 24,  rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 0, this, &(BF::skinBtn), 0, this->_t._btn, this->_t._ft);
    Btn *u = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(104.0, 120.0), "Respository", 24,  rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 0, this, &(BF::repoLink), 0, this->_t._btn, this->_t._ft);
    Btn *o = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-100.0, 120.0), "Options", 24, rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 0, this, &(BF::optBtn), 0, this->_t._btn, this->_t._ft);
    Btn *q = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 180.0), "Quit Game", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 0, this, &(BF::quitBtn), 0, this->_t._btn, this->_t._ft);
    Btn *d = new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 5, this, &(BF::backBtn), 0, this->_t._btn, this->_t._ft);
    Btn *ds = new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::backBtn), 0, this->_t._btn, this->_t._ft);
    Btn *lf = new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(104.0, 0.0), "Fight", 24,  rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 2, this, &(BF::launchGame), 0, this->_t._btn, this->_t._ft);
    Btn *lb = new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(-100.0, 0.0), "Back", 24, rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 2, this, &(BF::backBtn), 0, this->_t._btn, this->_t._ft);
    Btn *f = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), "FullScreen: OFF", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::fullScreen), 0, this->_t._btn, this->_t._ft);
    Btn *r = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 60.0), "Resolution: 800 x 600", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::resolutionBtn), 0, this->_t._btn, this->_t._ft);
    Btn *ms = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 120.0), "Map size: Small", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 1, this, &(BF::mapSize), 0, this->_t._btn, this->_t._ft);
    Btn *sa = new Btn(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(-340.0, 0.0), "+", 24, rl::Rectangle(596,0,40,40), "../assets/musics/click.wav", 5, this, &(BF::addSkin), 0, this->_t._btn, this->_t._ft);
    Btn *sr = new Btn(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(-290.0, 0.0), "-", 24, rl::Rectangle(596,0,40,40), "../assets/musics/click.wav", 5, this, &(BF::removeSkin), 0, this->_t._btn, this->_t._ft);
    Input *i = new Input(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(-50.0, 0.0), _manager->_settings._optSkin, 16, 5, 24, this, this->_t._btn, this->_t._ft);
    Btn *lp = new Btn(rl::Vec2(1.0/2, 4.0/20), rl::Vec2(270.0, 0.0), "Load Preview", 24, rl::Rectangle(400,0,196,40), "../assets/musics/click.wav", 5, this, &(BF::loadSkin), (void *)preview, this->_t._btn, this->_t._ft);
    List *ls = new List(rl::Vec2(1.0/2, 7.0/20), rl::Vec2(-350, 0.0), rl::Vec2(0.0, 35.0), 24, 5, this, &(_manager->_settings._skins), &(BF::previewSkin), preview, this->_t._ft, true, 4);
    //Btn *p = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), "Play", 24, rl::Rectangle(0,0,400,40), "../assets/musics/click.wav", 0, this, &(BF::playBtn));
    _manager->addComponent(mm);
    _manager->addComponent(lf);
    _manager->addComponent(lb);
    _manager->addComponent(player);
    _manager->addComponent(p);
    _manager->addComponent(s);
    _manager->addComponent(u);
    _manager->addComponent(o);
    _manager->addComponent(q);
    _manager->addComponent(d);
    _manager->addComponent(f);
    _manager->addComponent(r);
    _manager->addComponent(ds);
    _manager->addComponent(ms);
    _manager->addComponent(i);
    _manager->addComponent(sa);
    _manager->addComponent(sr);
    _manager->addComponent(lp);
    _manager->addComponent(ls);
    _manager->addComponent(preview);
    //Background *bg = new Background(rl::Vec3(1.0f, -23.0f, -2.0f), 3);
    //_manager->addComponent(bg);
    this->generateMap(medium);
    _win->changeFps(60);
}

Bomberman::~Bomberman()
{
    rl::Sound::CloseAudioDevice();
    delete _font;
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
                            rl::Color(255, 255, 255, 255), true, 3, this->_t._sb));
        }
    }

    // Create the border X
    for (int i = 0; i < x; i += 1) {
        _manager->addComponent(new Wall(rl::Vec3(i, 0.0f, 0.0f),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, this->_t._sb));
        _manager->addComponent(new Wall(rl::Vec3(i, 0.0f, y),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, this->_t._sb));
    }

    // Create the border Y
    for (int i = 1; i < y; i += 1) {
        _manager->addComponent(new Wall(rl::Vec3(0.0f, 0.0f, i),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, this->_t._sb));
        _manager->addComponent(new Wall(rl::Vec3(x - 1, 0.0f, i),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(255, 255, 255, 255), true, 3, this->_t._sb));
    }
}

void Bomberman::launch()
{
    while (!_win->ShouldClose() && !_ending) {
        _win->clearBackground(rl::Color(255, 255, 255, 255));
        _win->beginDrawing();

        _font->drawFPS(5, 25);
        _manager->handleEvent();
        _manager->simulate();
        _manager->renderAll();
        _win->endDrawing();
    }
}