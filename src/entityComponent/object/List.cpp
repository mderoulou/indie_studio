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
           void (*fptr)(Bomberman *, void *, std::string),
           void *data,
           std::shared_ptr<rl::Font> font,
           bool rm,
           uint32_t many) :
    _origin(origin),
    _offset(offset),
    _space(space),
    _win(win),
    _font(font)
{
    _scene = scene;
    _pSize = pSize;
    _text = text;
    _data = data;
    _rm = rm;
    _many = many;
    _ptr = fptr;
}

void List::render(rl::Camera3d *cam)
{
    uint32_t index = 0;
    rl::Vec2 pos(_origin.x * ((float)_win->_win->getScreenWidth()) + _offset.x, _origin.y * ((float)_win->_win->getScreenHeight()) + _offset.y);
    std::string dup;

    for (auto str : *_text) {
        rl::Vec2 size = _font->MesasureText(str, _pSize, 0.0);
        //rl::Rectangle rec(pos.x + _space.x * index, pos.y + _space.y * index, size.x, size.y);
        //rec.draw(rl::Color(255,0,0,255));
        if (_rm) {
            if (str.size() <= _many)
                continue;
            dup = str.substr(0, str.size() - _many);
            _font->drawTextEx(dup, rl::Vec2(pos.x + _space.x * index, pos.y + _space.y * index), _pSize, 0.0, rl::Color(0, 0, 0, 255));

        } else
            _font->drawTextEx(str, rl::Vec2(pos.x + _space.x * index, pos.y + _space.y * index), _pSize, 0.0, rl::Color(0, 0, 0, 255));
        index++;
    }
}

void List::handleEvent()
{
    if (!_ptr)
        return;
    uint32_t index = 0;
    std::string dup;
    rl::Vec2 pos(_origin.x * ((float)_win->_win->getScreenWidth()) + _offset.x, _origin.y * ((float)_win->_win->getScreenHeight()) + _offset.y);
    rl::Vec2 mousePos = rl::Mouse::GetMousePosition();
    for (auto str : *_text) {
        rl::Vec2 size = _font->MesasureText(str, _pSize, 0.0);
        rl::Rectangle rect(pos.x + _space.x * index, pos.y + _space.y * index, size.x, size.y);
        if (rect.checkCollision(mousePos) && rl::Mouse::IsMouseButtonReleased(::MouseButton::MOUSE_LEFT_BUTTON)) {
            if (_rm) {
                if (str.size() <= _many)
                    continue;
                dup = str.substr(0, str.size() - _many);
                _ptr(_win, _data, dup);
            } else
                _ptr(_win, _data, str);
        }
        index++;
    }
}