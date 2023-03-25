#include <globals.h>

void levelTwo()
{
    int MAX_TEXTURES = 1;

    // Load textures
    Texture2D textures[MAX_TEXTURES] = {
        LoadTexture("../res/tweezers.png")
    };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pauseMenu();
        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        EndDrawing();
    }
    // Unload textures
    for (int i = 0; i < MAX_TEXTURES; i++)
    {
        UnloadTexture(textures[i]);
    }

    // De-initialization
    CloseWindow();

}