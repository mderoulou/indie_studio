/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "../Object.hpp"

class Text : public Object2D
{
    public:
        Text(   const rl::Vec2 &origin,
                const rl::Vec2 &offset,
                int pSize,
                int scene,
                Bomberman *win,
                std::shared_ptr<std::string> text,
                std::shared_ptr<rl::Font> font,
                rl::Color color = rl::Color(255,255,255,255));
        void render(rl::Camera3d *cam) override;
    private:
        int _pSize;
        rl::Vec2 _origin;
        rl::Vec2 _offset;
        std::shared_ptr<std::string> _text;
        std::shared_ptr<rl::Font> _font;
        Bomberman *_win;
        rl::Color _color;
};

#endif /* !TEXT_HPP_ */