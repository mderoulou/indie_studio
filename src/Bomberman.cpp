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
    _win = new rl::Window(800, 600, "Indie Studio");
    rl::Sound::InitAudioDevice();
    _font = new rl::Font();
    _manager = new ComponentManager();
    Player *player = new Player(rl::Vec3(1.0f, 0.0f, 1.0f), 0.4f, rl::Color(255, 255, 255, 255), 3, true);
    Btn *p = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), "Play", 24, rl::Rectangle(0,0,400,40), "../assets/sound/click.wav", 0, this, &(BF::playBtn));
    Btn *s = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 60.0), "Skins", 24,  rl::Rectangle(0,0,400,40), "../assets/sound/click.wav", 0, this, &(BF::skinBtn));
    Btn *u = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(104.0, 120.0), "Respository", 24,  rl::Rectangle(400,0,196,40), "../assets/sound/click.wav", 0, this, &(BF::repoLink));
    Btn *o = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-100.0, 120.0), "Options", 24, rl::Rectangle(400,0,196,40), "../assets/sound/click.wav", 0, this, &(BF::optBtn));
    Btn *q = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 180.0), "Quit Game", 24, rl::Rectangle(0,0,400,40), "../assets/sound/click.wav", 0, this, &(BF::quitBtn));
    Btn *d = new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0,0,400,40), "../assets/sound/click.wav", 5, this, &(BF::backBtn));
    Btn *ds = new Btn(rl::Vec2(1.0/2, 19.0/20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0,0,400,40), "../assets/sound/click.wav", 1, this, &(BF::backBtn));
    Btn *f = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), "FullScreen: OFF", 24, rl::Rectangle(0,0,400,40), "../assets/sound/click.wav", 1, this, &(BF::fullScreen));
    Btn *r = new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 60.0), "Resolution: 800 x 600", 24, rl::Rectangle(0,0,400,40), "../assets/sound/click.wav", 1, this, &(BF::resolutionBtn));
    Input *i = new Input(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(0.0, 0.0), _manager->_optSkin, 16, 5, 24, this);
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
    _manager->addComponent(i);

    this->generateMap(10, 10);
    _win->changeFps(60);
}

Bomberman::~Bomberman()
{
    rl::Sound::CloseAudioDevice();
    delete _font;
    delete _win;
    delete _manager;
}

void Bomberman::generateMap(int x, int y)
{
    // Create the ground
    for (int i = 0; i < x; i += 1) {
        for (int j = 0; j < y; j += 1) {
            _manager->addComponent(new Wall(rl::Vec3(i, -1.0f, j),
                            rl::Vec3(1.0f, 1.0f, 1.0f),
                            rl::Color(255, 255, 255, 255), true, 3));
        }
    }

    // Create the border X
    for (int i = 0; i < x; i += 1) {
        _manager->addComponent(new Wall(rl::Vec3(i, 0.0f, 0.0f),
                            rl::Vec3(1.0f, 1.0f, 1.0f),
                            rl::Color(255, 255, 255, 255), true, 3));
        _manager->addComponent(new Wall(rl::Vec3(i, 0.0f, y),
                            rl::Vec3(1.0f, 1.0f, 1.0f),
                            rl::Color(255, 255, 255, 255), true, 3));
    }

    // Create the border Y
    for (int i = 1; i < y; i += 1) {
        _manager->addComponent(new Wall(rl::Vec3(0.0f, 0.0f, i),
                            rl::Vec3(1.0f, 1.0f, 1.0f),
                            rl::Color(255, 255, 255, 255), true, 3));
        _manager->addComponent(new Wall(rl::Vec3(x - 1, 0.0f, i),
                            rl::Vec3(1.0f, 1.0f, 1.0f),
                            rl::Color(255, 255, 255, 255), true, 3));
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