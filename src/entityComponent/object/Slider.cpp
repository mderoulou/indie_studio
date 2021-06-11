/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Slider
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

Slider::Slider(
            const rl::Vec2 &pos,
            const rl::Vec2 &offset,
            int pSize,
            const rl::Rectangle &bsrc,
            const rl::Rectangle &csrc,
            int scene,
            const std::string &text,
            Bomberman *m,
            void (*fptr)(Bomberman *, Slider *, void *),
            void *data,
            std::shared_ptr<rl::Texture> back,
            std::shared_ptr<rl::Texture> cursor,
            std::shared_ptr<rl::Font> font,
            const rl::Color &color
        )
    : _bsrc(bsrc),
      _csrc(csrc),
      _font(font),
      _back(back),
      _cursor(cursor),
      _bound(pos.x, pos.y, bsrc.width, bsrc.height)
{
    _win = m;
    _scene = scene;
    _pos = rl::Vec2(0.0, 0.0);
    _cpos = rl::Vec2(0.95, 1.0);
    _offset = offset;
    _clicked = false;
    _color = color;
    _ptr = fptr;
    _text = text;
    _data = data;
    _pSize = pSize;
    _relative = pos;
}

void Slider::render(rl::Camera3d *cam)
{
    rl::Vec2 pos(((float)_win->_win->getScreenWidth()) * _relative.x - _bsrc.width / 2.0 + _offset.x, ((float)_win->_win->getScreenHeight()) * _relative.y - _bsrc.height / 2.0 + _offset.y);
    rl::Rectangle final(_csrc.x, _csrc.y, _csrc.width, _csrc.height);

    _bound.x = pos.x;
    _bound.y = pos.y;
    final.y += _csrc.height * (_hover ? 1 : 0);
    _back->drawRec(_bsrc, pos, _color);
    _cursor->drawRec(final, rl::Vec2(pos.x + _bsrc.width * _cpos.x, pos.y), _color);
    _font->drawTextEx(_text, rl::Vec2(pos.x + _bsrc.width / 2.0 - _text.length() * _pSize / 4.0, pos.y + _bsrc.height / 2.0 - _pSize / 2.0), _pSize, 0.0, rl::Color(255,255,255,255));
}

void Slider::handleEvent()
{
    rl::Vec2 mousePos = rl::Mouse::GetMousePosition();

    _clicked = false;
    _hover = false;
    if (_bound.checkCollision(mousePos)) {
        if (rl::Mouse::IsMouseButtonDown(::MouseButton::MOUSE_LEFT_BUTTON))
            _clicked = true;
        _hover = true;
    }
    if (_clicked) {
        _cpos.x = (mousePos.x - _bound.x) / _bsrc.width;
        if (_cpos.x > 0.95)
            _cpos.x = 0.95;
        if (_ptr)
            _ptr(_win, this, _data);
    }
}