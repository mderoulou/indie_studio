/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "../Object.hpp"

class Input : public Object2D {
    public:
        Input(const rl::Vec2 &pos,
              const rl::Vec2 &offset,
              std::string &ptr,
              int maxLen,
              int scene,
              int pSize,
              Bomberman *m,
              std::shared_ptr<rl::Texture> texture = nullptr,
              std::shared_ptr<rl::Font> font = nullptr,
              const rl::Rectangle &src = rl::Rectangle(636.0, 0.0, 404.0, 44.0),
              const rl::Color &color = rl::Color(255, 255, 255, 255));
        rl::Vec2 _pos; // Pos of input
        rl::Color _color; // Color
        void render(rl::Camera3d *cam) override;
        void handleEvent() override;

    private:
        rl::Rectangle _src; // Rect for texture
        rl::Vec2 _relative; // Percentage position for all windows
        rl::Vec2 _offset; // Offset added to relative
        std::shared_ptr<rl::Texture> _texture; // Texture of input
        std::shared_ptr<rl::Font> _font; // Font of text 2 draw
        std::string &_ptr; // Ref of string
        rl::Rectangle _bound; //Rectangle for collision
        bool _isActive;
        int _pSize;
        int _maxLen;
        Bomberman *_win; // Ptr to main class
};

#endif /* !INPUT_HPP_ */