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
    rl::Font _font;
    rl::Color _color;
};

#endif /* !TEXT_HPP_ */