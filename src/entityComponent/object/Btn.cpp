/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Btn
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

Btn::Btn(const rl::Vec2 &pos, const rl::Rectangle &src, const std::string &textureFile, const std::string &soundFile, int scene, Bomberman *m, void (*fptr)(Bomberman *), const rl::Color &color)
    : _src(src),
    _bound(pos.x, pos.y, src.width, src.height),
    _texture(textureFile),
    _sound(soundFile)
{
    _win = m;
    _scene = scene;
    _pos = pos;
    _btnState = 0;
    _clicked = false;
    _color = color;
    _ptr = fptr;
}

void Btn::render(rl::Camera3d *cam)
{
    rl::Rectangle final(_src.x, _src.y, _src.width, _src.height);

    final.y = final.height * _btnState;
    _texture.drawRec(final, _pos, _color);
}

void Btn::handleEvent()
{
    Vector2 mousePos = rl::Mouse::GetMousePosition();

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
        _sound.play();
        _ptr(_win);
    }

}

void Btn::move(rl::Vec3 newPos)
{
    (void)newPos;
}