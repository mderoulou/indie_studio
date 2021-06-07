/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Btn
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

Btn::Btn(rl::Vec2 pos, rl::Rectangle rect, std::string textureFile, std::string soundFile, rl::Color color)
    : _textureRect(rect),
    _texture(textureFile),
    _sound(soundFile)
{
    _pos = pos;
    _btnState = 0;
    _clicked = false;
    _color = color;
}