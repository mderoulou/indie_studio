/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Btn
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

Btn::Btn(const rl::Vec2 &pos,
         const rl::Vec2 &offset,
         const std::string &text,
         int pSize,
         const rl::Rectangle &src,
         std::shared_ptr<rl::Sound> soundFile,
         int scene,
         Bomberman *m,
         void (*fptr)(Bomberman *, Btn *, void *),
         void *data,
         std::shared_ptr<rl::Texture> textureFile,
         std::shared_ptr<rl::Font> font,
         const rl::Color &color)
    : _src(src),
    _font(font),
    _bound(pos.x, pos.y, src.width, src.height),
    _texture(textureFile),
    _sound(soundFile)
{
    _win = m;
    _scene = scene;
    _relative = pos;
    _pos = rl::Vec2(0.0, 0.0);
    _offset = offset;
    _btnState = 0;
    _clicked = false;
    _color = color;
    _ptr = fptr;
    _text = text;
    _pSize = pSize;
    _data = data;
}

void Btn::render(rl::Camera3d *cam)
{
    rl::Vec2 pos(((float)_win->_win->getScreenWidth()) * _relative.x - _src.width / 2.0 + _offset.x, ((float)_win->_win->getScreenHeight()) * _relative.y - _src.height / 2.0 + _offset.y);
    rl::Rectangle final(_src.x, _src.y, _src.width, _src.height);

    _pos.x = pos.x;
    _pos.y = pos.y;
    _bound.x = _pos.x;
    _bound.y = _pos.y;
    final.y = final.height * _btnState;
    _texture->drawRec(final, _pos, _color);
    _font->drawTextEx(_text, rl::Vec2(_pos.x + _src.width / 2 - _text.length() * _pSize / 4, _pos.y + _src.height / 2 - _pSize / 2), _pSize, 0.0, _btnState ? rl::Color(255,255,160, 255) : rl::Color(221,221,221,255));
}

void Btn::handleEvent()
{
    rl::Vec2 mousePos = rl::Mouse::GetMousePosition();

    _clicked = false;
    if (_bound.checkCollision(mousePos)) {
            if (rl::Mouse::IsMouseButtonDown(::MouseButton::MOUSE_LEFT_BUTTON))
                _btnState = 2;
            else
                _btnState = 1;
            if (rl::Mouse::IsMouseButtonReleased(::MouseButton::MOUSE_LEFT_BUTTON))
                _clicked = true;
    } else
        _btnState = 0;
    if (_clicked) {
        _sound->setVolume(_win->_manager->_settings._sVol);
        _sound->play();
        _ptr(_win, this, _data);
    }
}