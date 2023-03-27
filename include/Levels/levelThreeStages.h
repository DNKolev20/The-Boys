#include <globals.h>

void levelThreeStageOne()
{
    Texture2D textures = LoadTexture("../res/locked.png");

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pauseMenu();
        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawTexture(textures, 0, 0, WHITE);

        EndDrawing();
    }
    // Unload textures
    UnloadTexture(textures);

    // De-initialization
    CloseWindow();      
}