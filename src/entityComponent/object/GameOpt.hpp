/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** GameOpt
*/

#ifndef GAMEOPT_HPP_
#define GAMEOPT_HPP_

#include "../Object.hpp"

/*
** TYPES :
** 0 void
** 1 ply
** 2 ia
*/ 
class GameOpt : public Object2D {
    public:
        GameOpt(Bomberman *win, int scene);
        std::vector<std::string> _names;
        std::vector<int> _types;
        std::vector<Preview *> _previews;
        Bomberman *_win;
};

#endif /* !GAMEOPT_HPP_ */