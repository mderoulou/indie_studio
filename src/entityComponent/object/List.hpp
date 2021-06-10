/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** List
*/

#ifndef LIST_HPP_
#define LIST_HPP_

#include <vector>
#include "../Object.hpp"

class List : public Object2D {
    public:
        List( const rl::Vec2 &origin,
              const rl::Vec2 &offset,
              const rl::Vec2 &space,
              int pSize,
              int scene,
              Bomberman *win,
              std::vector<std::string> *text,
              const std::string &font = "../assets/minecraftia.ttf");

        void render(rl::Camera3d *cam) override;
    private:
        int _pSize;
        rl::Vec2 _origin;
        rl::Vec2 _offset;
        rl::Vec2 _space;
        rl::Font _font;
        std::vector<std::string> *_text;
        Bomberman *_win;
};

#endif /* !LIST_HPP_ */