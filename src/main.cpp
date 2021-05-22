#include "rayLib.hpp"

int main()
{
    // Our Raylib

    rl::Window win(600, 200, "Raylib");

    win.changeFps(60);

    while (!win.Close()) {
        win.beginDrawing();

        win.clearBackground(rl::Color());
        win.endDrawing();
    }

    return (0);
}