/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Font Class
*/

#include "Gamepad.hpp"

Control::Control() {}
Control::Control(rl::Font f) : font(f) {}
Control::~Control() {}

int GamepadManager::getActiveController() { 
    int gmpadButton = GetGamepadButtonPressed();
    if (gmpadButton != -1) {
        for (int i = 0; i < 4; i++) {
            if (IsGamepadAvailable(i) && IsGamepadButtonDown(i, gmpadButton)) {
                return i;
            }
        }
    }
    return -1;
}
bool GamepadManager::gamepadAvailable() { 
    for (int i = 0; i < 4; i++)
        if (IsGamepadAvailable(i))
            return true;
    return false;
}

Gamepad::Gamepad() {}
Gamepad::Gamepad(rl::Font f) : Control(f) {}
Gamepad::~Gamepad() {}
float Gamepad::isKeyUp() {
    if (keyUp >= 32)
        return resolveAxis(keyUp - 32, axisUp);
    return IsGamepadButtonDown(gamepad, keyUp);
}
float Gamepad::isKeyDown() {
    if (keyDown >= 32)
        return resolveAxis(keyDown - 32, axisDown);
    return IsGamepadButtonDown(gamepad, keyDown);
}
float Gamepad::isKeyLeft() {
    if (keyLeft >= 32)
        return resolveAxis(keyLeft - 32, axisLeft);
    return IsGamepadButtonDown(gamepad, keyLeft);
}
float Gamepad::isKeyRight() {
    if (keyRight >= 32)
        return resolveAxis(keyRight - 32, axisRight);
    return IsGamepadButtonDown(gamepad, keyRight);
}
int Gamepad::isKeyUse() {
    return IsGamepadButtonDown(gamepad, keyUse);
}
void Gamepad::init() {
    int gmpadButton = GetGamepadButtonPressed();
    if (gamepad == -1) {
        font.drawText("Press a button to identify your gamepad.", 0, 0, 32, rl::Color(255,0,0,255));
        if (gmpadButton != -1)
            for (int i = 0; i < 4; i++)
                if (IsGamepadAvailable(i) && IsGamepadButtonDown(i, gmpadButton)) {
                    lastKey = gmpadButton;
                    gamepad = i;
                }
    } else {
        int axisCount = GetGamepadAxisCount(gamepad);
        if (axisCount > 4) {
            axisCount = 4;
        }
        //float axe = 0;
        //int axisInfo = -1;
        for (int i = 0; i < axisCount; i++) {
            float naxe = GetGamepadAxisMovement(gamepad, i);
            //if (naxe == 1 || naxe == -1) {
            //    axe = naxe;
            //    axisInfo = i;
            //}
        }
        if (keyUp == -1) {
            font.drawText("Button / Axis to go up :", 0, 0, 32, rl::Color(255,0,0,255));
            setKey(keyUp, axisUp);
        } else if (keyDown == -1) {
            font.drawText("Button / Axis to go down :", 0, 0, 32, rl::Color(255,0,0,255));
            setKey(keyDown, axisDown);
        } else if (keyLeft == -1) {
            font.drawText("Button / Axis to go left :", 0, 0, 32, rl::Color(255,0,0,255));
            setKey(keyLeft, axisLeft);
        } else if (keyRight == -1) {
            font.drawText("Button / Axis to go Right :", 0, 0, 32, rl::Color(255,0,0,255));
            setKey(keyRight, axisRight);
        } else if (keyUse == -1) {
            font.drawText("Button to use object :", 0, 0, 32, rl::Color(255,0,0,255));
            if (gmpadButton != -1 && gmpadButton != lastKey) {
                keyUse = gmpadButton;
            }
        } else {
            initialized = true;
        }
    }
}

float Gamepad::resolveAxis(int axis, bool inv) {
    //std::cout << "Resolving axis " << axis << std::endl;
    return inv ? GetGamepadAxisMovement(gamepad, axis) : -GetGamepadAxisMovement(gamepad, axis);
}

bool Gamepad::setKey(int &key, bool &axisOrientation) {
    if (key != -1)
        return false;
    int gmpadButton = GetGamepadButtonPressed();
    int axisCount = GetGamepadAxisCount(gamepad);
    if (axisCount > 4) {
        axisCount = 4;
    }
    bool orientation;
    int axisInfo = -1;
    for (int i = 0; i < axisCount; i++) {
        float naxe = GetGamepadAxisMovement(gamepad, i);
        if (naxe == 1 || naxe == -1) {
            orientation = naxe == -1 ? false : true;
            axisInfo = i;
        }
    }
    if (axisInfo != -1 && axisInfo == lastAxis && orientation == lastOrientation) {
        return true;
    } else if (axisInfo != -1) {
        //std::cout << "Set axis to " << axisInfo << std::endl;
        key = axisInfo + 32;
        axisOrientation = orientation;
        lastAxis = axisInfo;
        lastOrientation = orientation;
        lastKey = -1;
        return true;
    } else if (gmpadButton != -1 && gmpadButton != lastKey) {
        key = gmpadButton;
        return true;
    }
    return false;
}

Keyboard::Keyboard() {};
Keyboard::Keyboard(rl::Font f) : Control(f) {}
Keyboard::~Keyboard() {}
float Keyboard::isKeyUp() {
    return IsKeyDown(keyUp) ? 1 :  0;
}
float Keyboard::isKeyDown() {
    return IsKeyDown(keyDown) ? 1 :  0;
}
float Keyboard::isKeyLeft() {
    return IsKeyDown(keyLeft) ? 1 :  0;
}
float Keyboard::isKeyRight() {
    return IsKeyDown(keyRight) ? 1 :  0;
}
int Keyboard::isKeyUse() {
    return IsKeyDown(keyUse) ? 1 :  0;
}
void Keyboard::init() {
    int gmpadButton = GetKeyPressed();
    if (keyUp == -1) {
        font.drawText("Button to go up :", 0, 0, 32, rl::Color(255,0,0,255));
        if (gmpadButton != 0 && gmpadButton != lastKey) {
            keyUp = gmpadButton;
            lastKey = gmpadButton;
        }
    } else if (keyDown == -1) {
        font.drawText("Button to go down :", 0, 0, 32, rl::Color(255,0,0,255));
        if (gmpadButton != -0 && gmpadButton != lastKey) {
            keyDown = gmpadButton;
            lastKey = gmpadButton;
        }
    } else if (keyLeft == -1) {
        font.drawText("Button to go left :", 0, 0, 32, rl::Color(255,0,0,255));
        if (gmpadButton != -0 && gmpadButton != lastKey) {
            keyLeft = gmpadButton;
            lastKey = gmpadButton;
        }
    } else if (keyRight == -1) {
        font.drawText("Button to go Right :", 0, 0, 32, rl::Color(255,0,0,255));
        if (gmpadButton != -0 && gmpadButton != lastKey) {
            keyRight = gmpadButton;
            lastKey = gmpadButton;
        }
    } else if (keyUse == -1) {
        font.drawText("Button to use object :", 0, 0, 32, rl::Color(255,0,0,255));
        if (gmpadButton != -0 && gmpadButton != lastKey) {
            keyUse = gmpadButton;
            lastKey = gmpadButton;
        }
    } else {
        initialized = true;
    }
}