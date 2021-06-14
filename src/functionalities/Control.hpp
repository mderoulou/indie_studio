/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Controls
*/

#ifndef CONTROLS_HPP_
#define CONTROLS_HPP_

#include <memory>
#include <vector>
#include "../raylib/rayLib.hpp"

class Controls {
    public:
        Controls(uint16_t id);

        static int newControls();
        virtual float isKeyUp() = 0;
        virtual float isKeyDown() = 0;
        virtual float isKeyLeft() = 0;
        virtual float isKeyRight() = 0;
        virtual int isKeyUse() = 0;
        virtual int isKeyOther() = 0;
        uint16_t _id;
};

class KeyBoard : public Controls {
    public:
        KeyBoard(uint16_t id, std::vector<int> keys);
        float isKeyUp() override;
        float isKeyDown() override;
        float isKeyLeft() override;
        float isKeyRight() override;
        int isKeyUse() override;
        int isKeyOther() override;
    private:
        std::vector<int> _keys; // SIZE 6
};

class GamePad : public Controls {
    public:
        GamePad(uint16_t id) : Controls(id) {};
        float resolveAxis(int axis, bool inv);
        float isKeyUp() override;
        float isKeyDown() override;
        float isKeyLeft() override;
        float isKeyRight() override;
        int isKeyUse() override;
        int isKeyOther() override;
};

#endif /* !CONTROLS_HPP_ */