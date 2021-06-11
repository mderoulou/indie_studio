/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Slider
*/

#ifndef SLIDER_HPP_
#define SLIDER_HPP_

#include "../Object.hpp"

class Slider : public Object2D {
    public:
        Slider(
            const rl::Vec2 &pos,
            const rl::Vec2 &offset,
            int pSize,
            const rl::Rectangle &bsrc,
            const rl::Rectangle &csrc,
            int scene,
            const std::string &test,
            Bomberman *m,
            void (*fptr)(Bomberman *, Slider *, void *),
            void *data = nullptr,
            std::shared_ptr<rl::Texture> back = 0,
            std::shared_ptr<rl::Texture> cursor = 0,
            std::shared_ptr<rl::Font> font = 0,
            const rl::Color &color = rl::Color(255, 255, 255, 255)
        );
        void handleEvent() override;
        void render(rl::Camera3d *cam) override;

        rl::Rectangle _bsrc;
        rl::Rectangle _csrc;
        std::string _text;
        rl::Vec2 _pos;
        rl::Color _color;
        rl::Vec2 _cpos;

    private:
        bool _clicked;
        bool _hover;
        int _pSize;
        void *_data;
        rl::Rectangle _bound;
        std::shared_ptr<rl::Texture> _back;
        std::shared_ptr<rl::Texture> _cursor;
        std::shared_ptr<rl::Font> _font;
        rl::Vec2 _relative;
        rl::Vec2 _offset;
        Bomberman *_win;
        void (*_ptr)(Bomberman *, Slider *, void *);
};

#endif /* !SLIDER_HPP_ */