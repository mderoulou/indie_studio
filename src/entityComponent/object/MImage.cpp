/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Image
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

MImage::MImage(const std::string &path,
                Bomberman *win,
                rl::Vec2 pos,
                rl::Vec2 offset,
                rl::Color c)
{
    _win = win;
    _pos = pos;
    _offset = offset;
    _c = c;
    _img = std::make_shared<rl::Texture>(path);
}

void MImage::render(rl::Camera3d *cam)
{
    float x = ((float)_win->_win->getScreenWidth()) * _pos.x + _offset.x - (float)_img->getTexture().width / 2.0;
    float y = ((float)_win->_win->getScreenHeight()) * _pos.y + _offset.y - (float)_img->getTexture().height / 2.0; 
    _img->draw((int)x, (int)y, _c);
}