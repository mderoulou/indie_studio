#include "rayLib.hpp"

int main()
{
    // Our Raylib

    rl::Window win(600, 200, "Raylib");


    win.changeFps(60);


    while (!win.Close()) {
        BeginDrawing();

        //win.clearBackground(rl::Color(0, 0, 0, 255));

        EndDrawing();
    }

    return (0);
    // classic Raylib
    InitWindow(600, 600, "Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hey le cmake fontionne", 190, 200, 20, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}