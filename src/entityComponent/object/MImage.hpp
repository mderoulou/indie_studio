/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** MImage
*/

#ifndef MIMAGE_HPP_
#define MIMAGE_HPP_

#include "../Object.hpp"

class MImage : public Object2D {
    public:
        MImage(  const std::string &path,
                Bomberman *win,
                rl::Vec2 pos,
                rl::Vec2 offset,
                rl::Color c = rl::Color(255,255,255,255));
        void render(rl::Camera3d *cam) override;
    private:
        Bomberman *_win;
        std::shared_ptr<rl::Texture> _img;
        rl::Vec2 _pos;
        rl::Vec2 _offset;
        rl::Color _c;
};

#endif /* !MIMAGE_HPP_ */
