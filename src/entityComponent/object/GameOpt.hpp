/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** GameOpt
*/

#ifndef GAMEOPT_HPP_
#define GAMEOPT_HPP_

#include "../Object.hpp"
#include "../../functionalities/Control.hpp"

/*
** TYPES :
** 0 void
** 1 ply
** 2 ia
*/ 
class GameOpt : public Object2D {
    public:
        GameOpt(Bomberman *win, int scene, std::shared_ptr<rl::Font> font);
        
        void simulate() override;
        std::vector<std::string> _names; // Player Names -> skins /To save -< Taille fixe 4
        std::vector<int> _types; // Player Types -> cf TYPES UP /To save -< Taille fixe 4
        std::vector<std::shared_ptr<Preview>> _previews; // Previews ptr; (in component manager)
        std::vector<std::shared_ptr<Btn>> _btns; 
        std::vector<std::shared_ptr<Controls>> _controllers;
        std::vector<std::vector<int>> _keys;
        std::shared_ptr<rl::Font> _font;
        Bomberman *_win;
};

#endif /* !GAMEOPT_HPP_ */