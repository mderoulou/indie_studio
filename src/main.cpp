#include "rayLib.hpp"

int main()
{
    // Our Raylib

    rl::Window win(600, 200, "Raylib");
    rl::Vec2 vec2(0, 0);
    rl::Vec4 vec4(0, 0, 50, 50);
    win.changeFps(60);

    while (!win.Close()) {
        win.beginDrawing();
        win.clearBackground(rl::Color(0, 0, 0, 255));
        vec2.drawPixel(rl::Color(255, 0, 0, 255));
        vec4.drawLine(rl::Color(255, 0, 0, 255));
        win.endDrawing();
    }

    return (0);
}