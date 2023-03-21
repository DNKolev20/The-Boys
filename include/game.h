#include <globals.h>

void game()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Boys");
    
    SetTargetFPS(60);

    Texture scalpel = imageloader("../res/scalpel.png");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(scalpel, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, WHITE);

        DrawText("Test", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    UnloadTexture(scalpel);
    CloseWindow();
}