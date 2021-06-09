/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Window funct
*/

#include "Window.hpp"

// Window functions

rl::Window::Window(int width, int height, const std::string title)
    :_width(width), _height(height), _title(title), _fps(120)
{
    InitWindow(width, height, title.c_str());
    if (!IsWindowReady())
        throw WindowError("Bad Initialization\n");
    SetTargetFPS(_fps);
    _cursorEnabled = true;
}

rl::Window::~Window()
{
    if (this->ShouldClose())
        this->Close();
}

void rl::Window::Close()
{
    ::CloseWindow();
}

bool rl::Window::ShouldClose()
{
    return WindowShouldClose();
}

bool rl::Window::isReady()
{
    return IsWindowReady();
}

bool rl::Window::isFullscreen()
{
    return IsWindowFullscreen();
}

void rl::Window::setFullscreen()
{
    ToggleFullscreen();
}

void rl::Window::setWindowIcon(rl::Image img)
{
    SetWindowIcon(img.getImg());
}

void rl::Window::changeTitle(std::string title)
{
    SetWindowTitle(title.c_str());
}

void rl::Window::changeFps(int fps)
{
    _fps = fps;
    SetTargetFPS(_fps);
}

void rl::Window::setPosition(int x, int y)
{
    SetWindowPosition(x, y);
}

int rl::Window::getFps()
{
    return GetFPS();
}

void rl::Window::setWindowSize(int width, int height)
{
    _width = width;
    _height = height;

    SetWindowSize(width, height);
}

// Cursor

void rl::Window::showCursor()
{
    ShowCursor();
    _cursorEnabled = true;
}

void rl::Window::hideCursor()
{
    HideCursor();
    _cursorEnabled = false;
}

void rl::Window::lockCursor()
{
    DisableCursor();
}

void rl::Window::unlockCursor()
{
    EnableCursor();
}

bool rl::Window::isCursorOnScreen()
{
    return IsCursorOnScreen();
}

// Draw Functions

void rl::Window::clearBackground(rl::Color color)
{
    ClearBackground(color);
}

void rl::Window::beginDrawing()
{
    BeginDrawing();
}

void rl::Window::endDrawing()
{
    EndDrawing();
}

// Grid

void rl::Window::drawGrid()
{
    DrawGrid(10, 1.0f);
}