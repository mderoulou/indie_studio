/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Input
*/

#include "Input.hpp"

Input::Input(rl::Vec2 pos, rl::Vec2 offset, std::string &ptr)
    : _ptr(ptr)
{
}

void Input::move(rl::Vec3 newPos)
{
    (void)newPos;
    _pos.x = ((float)_win->_win->getScreenWidth()) * _relative.x - _src.width / 2.0 + _offset.x;
    _pos.y = ((float)_win->_win->getScreenHeight()) * _relative.y - _src.height / 2.0 + _offset.y;
    _bound.x = _pos.x;
    _bound.y = _pos.y;
}