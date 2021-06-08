/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Btn
*/

#ifndef BTN_HPP_
#define BTN_HPP_

#include "../Object.hpp"

class Btn : public Object2D
{
    public:
        Btn(const rl::Vec2 &pos, const rl::Rectangle &src, const std::string &textureFile, const std::string &soundFile, int scene, Bomberman *m, void (*fptr)(Bomberman *), const rl::Color &color = rl::Color(255, 255, 255, 255));
        
        short _btnState;
        bool _clicked;
        rl::Rectangle _src;
        rl::Rectangle _bound;
        rl::Vec2 _pos;
        rl::Color _color;
        rl::Sound _sound;
        rl::Texture _texture;
        Bomberman *_win;
        void (*_ptr)(Bomberman *);

        void handleEvent() override;
        void render(rl::Camera3d *cam) override;
};

#endif /* !BTN_HPP_ */
