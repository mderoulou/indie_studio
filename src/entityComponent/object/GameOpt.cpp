/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** GameOpt
*/

#include "../Object.hpp"
#include "../Manager.hpp"

GameOpt::GameOpt(Bomberman *win, int scene)
    : _win(win),
    _types(4, 1)
{
    Preview *preview = nullptr;

    _scene = scene;
    _win = win;
    if (win->_manager->_settings._skins.size())
        for (int x = 0; x < 4; x++)
            _names.push_back(win->_manager->_settings._skins[0].substr(0, win->_manager->_settings._skins[0].size() - 4));
    else
        for (int x = 0; x < 4; x++)
            _names.push_back("skin");
    _win->_manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-300.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)0, win->_t._btn, _win->_t._ft), 2);
    _win->_manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-100.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)1, _win->_t._btn, _win->_t._ft), 2);
    _win->_manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(104.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)2, _win->_t._btn, _win->_t._ft), 2);
    _win->_manager->addComponent(new Btn(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(304.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)3, _win->_t._btn, _win->_t._ft), 2);
    preview = new Preview(rl::Vec3(0.5,2,13), 0.75, 2, -160, rl::Color(255,255,255,255), _win->_t._walking);
    _previews.push_back(preview);
    _win->_manager->addComponent(preview, 2);
    preview = new Preview(rl::Vec3(5,2,12), 0.75, 2, -180, rl::Color(255,255,255,255), _win->_t._walking);
    _previews.push_back(preview);
    _win->_manager->addComponent(preview, 2);
    preview = new Preview(rl::Vec3(10,2,12), 0.75, 2, -180, rl::Color(255,255,255,255), _win->_t._walking);
    _previews.push_back(preview);
    _win->_manager->addComponent(preview, 2);
    preview = new Preview(rl::Vec3(14.5,2,13), 0.75, 2, -200, rl::Color(255,255,255,255), _win->_t._walking);
    _previews.push_back(preview);
    _win->_manager->addComponent(preview, 2);
}