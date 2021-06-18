/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Text
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

Text::Text(     const rl::Vec2 &origin,
                const rl::Vec2 &offset,
                int pSize,
                int scene,
                Bomberman *win,
                std::shared_ptr<std::string> text,
                std::shared_ptr<rl::Font> font,
                rl::Color color) :
    _origin(origin),
    _offset(offset),
    _win(win),
    _color(color)
{
    _text = text;
    _pSize = pSize;
    _font = font;
    _scene = scene;
}

void Text::render(rl::Camera3d *cam)
{
    rl::Vec2 pos(_origin.x * ((float)_win->_win->getScreenWidth()) + _offset.x, _origin.y * ((float)_win->_win->getScreenHeight()) + _offset.y);
    std::cout << _origin.x << " & " << _origin.y << std::endl;
    std::cout << _offset.x << " & " << _offset.y << std::endl;
    std::cout << "Rendering text x " << (int)pos.x << " y " << (int)pos.y <<  std::endl;
    (*_text, pos, _pSize, 0.0, _color);
}