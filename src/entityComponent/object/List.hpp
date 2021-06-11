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
              void (*fptr)(Bomberman *, void *, std::string) = nullptr,
              void *data = nullptr,
              std::shared_ptr<rl::Font> font = nullptr,
              bool rm = false,
              uint32_t many = 0);

        void handleEvent() override;
        void render(rl::Camera3d *cam) override;
    private:
        int _pSize;
        rl::Vec2 _origin;
        rl::Vec2 _offset;
        rl::Vec2 _space;
        std::shared_ptr<rl::Font> _font;
        void (*_ptr)(Bomberman *, void *, std::string);
        void *_data;
        std::vector<std::string> *_text;
        Bomberman *_win;
        bool _rm;
        uint32_t _many;
};

#endif /* !LIST_HPP_ */