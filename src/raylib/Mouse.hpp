/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

namespace rl {
class Mouse {
    public:
        static Vector2 GetMousePosition() { return (::GetMousePosition()); };
        static bool IsMouseButtonDown(int btn) { return (::IsMouseButtonDown(btn)); };
        static bool IsMouseButtonPressed(int btn) { return (::IsMouseButtonPressed(btn)); };
        static bool IsMouseButtonReleased(int btn) { return (::IsMouseButtonReleased(btn)); };
};
}

#endif /* !MOUSE_HPP_ */