/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** KeyBoard
*/

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include "raylib.h"

namespace rl {

class KeyBoard {
    public:
        static int GetCharPressed() { return ::GetCharPressed(); };
        static int GetKeyPressed() { return ::GetKeyPressed(); };
        static bool IsKeyPressed(int key) { return ::IsKeyPressed(key); };
        static bool IsKeyReleased(int key) { return ::IsKeyReleased(key); };
        static bool IsKeyDown(int key) { return ::IsKeyDown(key); };
        static bool IsKeyUp(int key) { return ::IsKeyUp(key); };
};

}

#endif /* !KEYBOARD_HPP_ */