/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Input
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

Input::Input(const rl::Vec2 &pos,
             const rl::Vec2 &offset,
             std::string &ptr,
             int maxLen,
             int scene,
             int pSize,
             Bomberman *m,
             std::shared_ptr<rl::Texture> textureFile,
             std::shared_ptr<rl::Font> font,
             const rl::Rectangle &src,
             const rl::Color &color)
    : _ptr(ptr),
    _src(src),
    _font(font),
    _bound(pos.x, pos.y, src.width, src.height),
    _texture(textureFile)
{
    _win = m;
    _scene = scene;
    _relative = pos;
    _pos = rl::Vec2(0.0, 0.0);
    _offset = offset;
    _isActive = false;
    _color = color;
    _maxLen = maxLen;
    _pSize = pSize;
}

void Input::render(rl::Camera3d *cam)
{
    rl::Vec2 pos(((float)_win->_win->getScreenWidth()) * _relative.x - _src.width / 2.0 + _offset.x, ((float)_win->_win->getScreenHeight()) * _relative.y - _src.height / 2.0 + _offset.y);
    rl::Rectangle final(_src.x, _src.y, _src.width, _src.height);

    _pos.x = pos.x;
    _pos.y = pos.y;
    _bound.x = _pos.x;
    _bound.y = _pos.y;
    final.y = final.height * (_isActive ? 1 : 0);
    _texture->drawRec(final, _pos, _color);
    _font->drawTextEx(_ptr, rl::Vec2(_pos.x + _src.width / 2 - _ptr.length() * _pSize / 4, _pos.y + _src.height / 2 - _pSize / 2), _pSize, 0.0, _isActive ? rl::Color(255,255,255,255) : rl::Color(160,160,160,255));

}

void Input::handleEvent()
{
    rl::Vec2 mousePos = rl::Mouse::GetMousePosition();
    int key;

    if (_bound.checkCollision(mousePos)) {
        _isActive = true;
    } else
        _isActive = false;
    if (_isActive) {
        key = rl::KeyBoard::GetCharPressed();
        while (key > 0) {
            if ( ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122))&& _ptr.length() < _maxLen) // ONly alphanumeric
                _ptr.push_back(key);
            key = rl::KeyBoard::GetCharPressed();
        }
        if (rl::KeyBoard::IsKeyPressed(KEY_BACKSPACE) && _ptr.length())
            _ptr.pop_back();
    }
}