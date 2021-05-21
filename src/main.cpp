#include "raylib.h"

int main()
{
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