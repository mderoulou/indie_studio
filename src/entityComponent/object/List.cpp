/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** List
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

List::List(const rl::Vec2 &origin,
           const rl::Vec2 &offset,
           const rl::Vec2 &space,
           int pSize,
           int scene,
           Bomberman *win,
           std::vector<std::string> *text,
           const std::string &font) :
    _origin(origin),
    _offset(offset),
    _space(space),
    _win(win),
    _font(font)
{
    _scene = scene;
    _pSize = pSize;
    _text = text;
}

void List::render(rl::Camera3d *cam)
{
    uint32_t index = 0;
    rl::Vec2 pos(_origin.x * ((float)_win->_win->getScreenWidth()) + _offset.x, _origin.y * ((float)_win->_win->getScreenHeight()) + _offset.y);

    for (auto str : *_text) {
        _font.drawTextEx(str, rl::Vec2(pos.x + _space.x * index, pos.y + _space.y * index), _pSize, 0.0, rl::Color(0, 0, 0, 255));
        index++;
    }
}