/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "raylib.h"
#include "Vector.hpp"

namespace rl {

class Mouse {
    public:
        static rl::Vec2 GetMousePosition() {return (rl::Vec2(::GetMousePosition())); };
        static bool IsMouseButtonDown(int btn) { return (::IsMouseButtonDown(btn)); };
        static bool IsMouseButtonPressed(int btn) { return (::IsMouseButtonPressed(btn)); };
        static bool IsMouseButtonReleased(int btn) { return (::IsMouseButtonReleased(btn)); };
        static void ShowCursor() { ::ShowCursor(); };
        static void HideCursor() { ::HideCursor(); };
};
}

#endif /* !MOUSE_HPP_ */