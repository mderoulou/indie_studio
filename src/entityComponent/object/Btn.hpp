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
        Btn(const rl::Vec2 &pos,
            const rl::Vec2 &offset,
            const std::string &text,
            int pSize,
            const rl::Rectangle &src,
            const std::string &soundFile,
            int scene,
            Bomberman *m,
            void (*fptr)(Bomberman *, Btn *, void *),
            void *data = 0,
            const std::string &textureFile = "../assets/menus/btns.png",
            const rl::Color &color = rl::Color(255, 255, 255, 255),
            const std::string &font = "../assets/minecraftia.ttf");
        
        rl::Rectangle _src; //Rectangle for texture
        rl::Vec2 _pos; // Pos of btn
        rl::Color _color; // Filter of btn
        std::string _text; // Text on btn

        void handleEvent() override;
        void render(rl::Camera3d *cam) override;
        void move(rl::Vec3 newPos) override;

    private:
        short _btnState; //State of the button to move _texture rect
        bool _clicked; //Btn is clicked ?
        int _pSize; // Size of text
        void *_data; // Any data ???
        rl::Sound _sound; // Sound on click
        rl::Rectangle _bound; //Rectangle for collision
        rl::Texture _texture; // Texture of btn
        rl::Font _font; // Font of text 2 draw
        rl::Vec2 _relative; // Percentage position for all windows
        rl::Vec2 _offset; // Offset pos
        Bomberman *_win; // Ptr to main class
        void (*_ptr)(Bomberman *, Btn *, void *); // Action function
};

#endif /* !BTN_HPP_ */
