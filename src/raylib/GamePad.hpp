/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** GamePad
*/

#ifndef GAMEPAD_HPP_
#define GAMEPAD_HPP_

#include "raylib.h"

namespace rl {

class GamePad {
    public:
        static bool IsGamepadAvailable(int gamepad) { return ::IsGamepadAvailable(gamepad); };
        static bool IsGamepadName(int gamepad, const char *name) { return ::IsGamepadName(gamepad, name); };
        static const char *GetGamepadName(int gamepad) { return ::GetGamepadName(gamepad); };
        static bool IsGamepadButtonPressed(int gamepad, int button) { return ::IsGamepadButtonPressed(gamepad, button); };
        static bool IsGamepadButtonDown(int gamepad, int button) { return ::IsGamepadButtonDown(gamepad, button); };
        static bool IsGamepadButtonReleased(int gamepad, int button) { return ::IsGamepadButtonReleased(gamepad, button); };
        static bool IsGamepadButtonUp(int gamepad, int button) { return ::IsGamepadButtonUp(gamepad, button); };
        static int GetGamepadButtonPressed(void) { return ::GetGamepadButtonPressed(); };
        static int GetGamepadAxisCount(int gamepad) { return ::GetGamepadAxisCount(gamepad); };
        static float GetGamepadAxisMovement(int gamepad, int axis) { return ::GetGamepadAxisMovement(gamepad, axis); };
        static int SetGamepadMappings(const char *mappings) { return ::SetGamepadMappings(mappings); };
};

}

#endif /* !GAMEPAD_HPP_ */