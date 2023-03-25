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

        // Update
        int clickedTexture = CheckTextureClick(textures, MAX_TEXTURES);
        if (clickedTexture != -1)
        {
            // A texture has been clicked
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                // Move the texture if the left mouse button is down
                MoveTexture(&texturePositions[clickedTexture]);
            }
        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        // Draw textures
        for (int i = 0; i < MAX_TEXTURES; i++)
        {
            DrawTexture(textures[i], texturePositions[i].x, texturePositions[i].y, WHITE);
        }
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