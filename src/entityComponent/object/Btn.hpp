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
        
        short _btnState; //State of the button to move _texture rect
        bool _clicked; //Btn is clicked ?
        rl::Rectangle _src; //Rectangle for texture
        rl::Rectangle _bound; //Rectangle for collision
        rl::Vec2 _pos; // Pos of btn
        rl::Vec2 _relative; // Percentage position for all windows
        rl::Color _color; // Filter of btn
        rl::Sound _sound; // Sound on click
        rl::Texture _texture; // Texture of btn
        Bomberman *_win; // Ptr to main class
        void (*_ptr)(Bomberman *); // Action function

        void handleEvent() override;
        void render(rl::Camera3d *cam) override;
        void move(rl::Vec3 newPos) override;
};

#endif /* !BTN_HPP_ */
