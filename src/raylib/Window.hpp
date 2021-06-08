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
class Image;

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
        void setWindowIcon(rl::Image img);

        int getFps();
        static int getScreenWidth() { return ::GetScreenWidth(); };
        static int getScreenHeight() { return ::GetScreenHeight(); };

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

        // Draw grid

        void drawGrid();

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