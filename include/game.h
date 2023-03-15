#include <globals.h>

void game()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Boys");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Test", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
}