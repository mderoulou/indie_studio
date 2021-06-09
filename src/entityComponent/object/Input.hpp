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
        Input(rl::Vec2 pos, rl::Vec2 offset, std::string &ptr);
        void move(rl::Vec3 newPos) override;

    private:
        std::string &_ptr;
        bool _isActive;
};

#endif /* !INPUT_HPP_ */