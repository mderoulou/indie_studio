/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman functions
*/

#include "Bomberman.hpp"

Bomberman::Bomberman()
{
    _win = new rl::Window(1080, 720, "Indie Studio");
    _cam = new rl::Camera3d(rl::Vec3(5.0f, 20.0f, 30.0f),
                            rl::Vec3(0.0f, 0.0f, 0.0f),
                            rl::Vec3(0.0f, 1.0f, 0.0f),
                            45.0f, 0);
    _font = new rl::Font();
    _manager = new ComponentManager();

    Wall *test3 = new Wall(rl::Vec3(0.0f, 0.0f, 7.0f),
                            rl::Vec3(2.0f, 2.0f, 2.0f),
                            rl::Color(255, 255, 255, 255));

    _manager->addComponent(test3);

    Player *player = new Player(rl::Vec3(1.0f, 1.0f, 1.0f), 0.3f, rl::Color(255, 255, 255, 255));

    _manager->addComponent(player);

    _win->changeFps(60);
}

Bomberman::~Bomberman()
{
    delete _font;
    delete _win;
    delete _cam;
}

void Bomberman::launch()
{
    while (!_win->Close()) {
        _win->clearBackground(rl::Color(255, 255, 255, 255));
        _win->beginDrawing();
        _font->drawFPS(5, 5);

        _cam->beginMode();

        _manager->renderAll();

        _win->drawGrid();

        _cam->endMode();
        _win->endDrawing();
    }
}