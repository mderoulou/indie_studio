/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** EscManager
*/

#ifndef ESCMANAGER_HPP_
#define ESCMANAGER_HPP_

#include "../Object.hpp"

class EscManager : public Object2D {
    public:
        EscManager(Bomberman *win, int scene);
        void handleEvent() override;

    private:
        Bomberman *_win;
};

#endif /* !ESCMANAGER_HPP_ */
