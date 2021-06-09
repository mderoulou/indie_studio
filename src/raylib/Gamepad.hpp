/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Font Class
*/

#ifndef RL_GAMEPAD_
#define RL_GAMEPAD_

#include "raylib.h"
#include "Font.hpp"
#include <iostream>
#include <ostream>

class Control {
public:
    Control();
    Control(rl::Font f);
    virtual ~Control();
    virtual float isKeyUp() = 0;
    virtual float isKeyDown() = 0;
    virtual float isKeyLeft() = 0;
    virtual float isKeyRight() = 0;
    virtual int isKeyUse() = 0;
    virtual void init() = 0;
    bool initialized = false;
protected:
    int keyUp = -1;
    int keyDown = -1;
    int keyLeft = -1;
    int keyRight = -1;
    int keyUse = -1;
    rl::Font font;
};

class GamepadManager {
public:
    static int getActiveController();
    static bool gamepadAvailable();
};

class Gamepad : public Control {
public:
    Gamepad();
    Gamepad(rl::Font f);
    ~Gamepad();
    float isKeyUp();
    float isKeyDown();
    float isKeyLeft();
    float isKeyRight();
    int isKeyUse();
    void init();
    int gamepad = -1;
    bool axisUp = false;
    bool axisDown = true;
    bool axisLeft = false;
    bool axisRight = true;
private:
    float resolveAxis(int axis, bool inv);
    bool setKey(int &key, bool &axisOrientation);
    int lastAxis = -1;
    bool lastOrientation = false;
    int lastKey = -1;
    // false means axis max = -1 | true axis max = 1
};

class Keyboard : public Control {
public:
    Keyboard();
    Keyboard(rl::Font f);
    ~Keyboard();
    float isKeyUp();
    float isKeyDown();
    float isKeyLeft();
    float isKeyRight();
    int isKeyUse();
    void init();
private:
    int lastKey = 0;
};

#endif