#include <globals.h>

void levelTwoStageOne()
{
    Texture2D textures = LoadTexture("../res/needle.png");

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