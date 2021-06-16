/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Controls
*/

#include "Control.hpp"

/*****************************\
*                             *
*         CONTROLS            *
*                             *
\*****************************/

Controls::Controls(uint16_t id)
{
    _id = id;
}

int Controls::newControls()
{
    int btn = rl::GamePad::GetGamepadButtonPressed();
    int key = rl::KeyBoard::GetKeyPressed();

    if (key == 256)
        return (-1);
    for (int x = 0; btn != -1 && x < 4; x++) {
        if (rl::GamePad::IsGamepadAvailable(x) && rl::GamePad::IsGamepadButtonDown(x, btn)) {
            return (x);
        }
    }
    if (key > 0)
        return (4);
    return (-1);
}

/*****************************\
*                             *
*         KEYBOARD            *
*                             *
\*****************************/

KeyBoard::KeyBoard(uint16_t id, std::vector<int> keys)
    :  Controls(id)
{
    _keys = keys;
}

float KeyBoard::isKeyUp()
{
    return IsKeyDown(_keys[0]) ? 1.0 :  0.0;
}
float KeyBoard::isKeyDown()
{
    return IsKeyDown(_keys[1]) ? 1.0 :  0.0;
}
float KeyBoard::isKeyLeft()
{
    return IsKeyDown(_keys[2]) ? 1.0 :  0.0;
}
float KeyBoard::isKeyRight()
{
    return IsKeyDown(_keys[3]) ? 1.0 :  0.0;
}
int KeyBoard::isKeyUse()
{
    return IsKeyDown(_keys[4]) ? 1 :  0;
}

int KeyBoard::isKeyOther()
{
    return IsKeyDown(_keys[5]) ? 1 :  0;
}

/*****************************\
*                             *
*         GAMEPAD             *
*                             *
\*****************************/

float GamePad::resolveAxis(int axis, bool inv)
{
    return inv ? rl::GamePad::GetGamepadAxisMovement(_id, axis) : -rl::GamePad::GetGamepadAxisMovement(_id, axis);
}

float GamePad::isKeyUp()
{
    return GamePad::resolveAxis(1, 0);
}

float GamePad::isKeyDown()
{
    return GamePad::resolveAxis(1, 1);
}

float GamePad::isKeyLeft()
{
    return GamePad::resolveAxis(0, 0);
}

float GamePad::isKeyRight()
{
    return GamePad::resolveAxis(0, 1);
}

int GamePad::isKeyUse()
{
    return IsGamepadButtonDown(_id, 7);
}

int GamePad::isKeyOther()
{
    return IsGamepadButtonDown(_id, 6);
}