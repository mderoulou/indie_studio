/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Window Class
*/

#ifndef RL_WINDOW_
#define RL_WINDOW_

#include "rayLib.hpp"

namespace rl {

class Color;

class Window
{
    public:
        Window(int width, int height, std::string title);
        ~Window();

        // Window Functions

        bool isReady();
        bool isFullscreen();
        
        void setFullscreen();
        void setWindowSize(int width, int height);
        void setPosition(int x, int y);

        bool Close();
        void changeTitle(std::string title);
        void changeFps(int fps);

        int getFps();
        int getScreenWidth() const { return _width; };
        int getScreenHeight() const { return _height; };

        // Cursor Functions

        void showCursor();
        void hideCursor();
        void lockCursor();
        void unlockCursor();
        bool isCursorOnScreen();

        // Draw Functions
        void clearBackground(rl::Color color);
        void beginDrawing();
        void endDrawing();

    private:

        // Window properties
        int _width;
        int _height;
        std::string _title;
        int _fps;

        // Cursor properties
        bool _cursorEnabled;
};
}

#endif