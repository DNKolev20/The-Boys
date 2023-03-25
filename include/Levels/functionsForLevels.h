#include <globals.h>

extern int currentStage;

void DrawDashedLine(Vector2 startPos, Vector2 endPos, float dashLength, float gapLength, float offset, Color color)
{
    Vector2 dir = Vector2Subtract(endPos, startPos);
    float length = Vector2Length(dir);
    dir = Vector2Normalize(dir);
    
    float remainingLength = length;
    Vector2 currentPos = startPos;

    while (remainingLength > 0) {
        Vector2 dashStart = currentPos;
        Vector2 dashEnd = Vector2Add(currentPos, Vector2Scale(dir, fmin(remainingLength, dashLength)));
        
        if (offset > 0) {
            float offsetLength = fmod(offset, dashLength + gapLength);
            if (offsetLength > 0 && offsetLength < dashLength) {
                float dashOffset = dashLength - offsetLength;
                dashStart = Vector2Add(dashStart, Vector2Scale(dir, dashOffset));
            }
            offset -= fmin(offsetLength, dashLength + gapLength);
        }
        
        DrawLineEx(dashStart, dashEnd, 2, color);

        remainingLength -= dashLength;
        currentPos = Vector2Add(dashEnd, Vector2Scale(dir, gapLength));
    }
}

void fadeBetweenStages(float fadeTime) 
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    int alpha = 255;
    float fadeTimer = 0.0f;

    SetTargetFPS(60);

    while (fadeTimer < fadeTime) {
        fadeTimer += GetFrameTime();
        alpha = (int)(255 * (1.0f - fadeTimer / fadeTime));

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        // Draw your game scene for the current stage here

        DrawRectangle(0, 0, screenWidth, screenHeight, Color{ 0, 0, 0, (unsigned char)alpha });

        EndDrawing();
    }

    currentStage++;
    levelOne();
}

void startCutting()
{
    Texture2D background = LoadTexture("../res/Level1_images/stage1_pre-cut.png");
    Texture2D scalpel = LoadTexture("../res/scalpel.png");

    // Define animation variables
    Vector2 startPos = { 967, 140 }; // Starting position of image
    Vector2 endPos = { 951, 939 }; // Ending position of image
    Vector2 currPos = startPos; // Current position of image
    float animationTime = 0.0f; // Time elapsed in animation
    float animationDuration = 2.0f; // Duration of animation in seconds

    while (!WindowShouldClose())
    {
        // Get the current screen size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the aspect ratio of the texture and the screen
        float textureRatio = (float)background.height / (float)background.width;
        float screenRatio = (float)screenHeight / (float)screenWidth;

        float scale = 1.0f;

        // Determine the scale factor to maintain aspect ratio and fill the screen
        if (textureRatio > screenRatio) 
        {
            scale = (float)screenHeight / (float)background.height;
        }
        else 
        {
            scale = (float)screenWidth / (float)background.width;
        }

        // Calculate the size of the background after scaling
        float textureWidth = background.width * scale;
        float textureHeight = background.height * scale;

        // Calculate the position to center the background on the screen
        float posX = (screenWidth - textureWidth) / 2.0f;
        float posY = (screenHeight - textureHeight) / 2.0f;

        // Update animation
        if (animationTime < animationDuration) 
        {
            float t = animationTime / animationDuration; // Calculate normalized time
            currPos.x = startPos.x + (endPos.x - startPos.x) * t; // Calculate current x position
            currPos.y = startPos.y + (endPos.y - startPos.y) * t; // Calculate current y position
            animationTime += GetFrameTime(); // Increment animation time
        }
        else
        {
            currentStage++;
            std::cout << currentStage;
            levelOne();
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        // Draw texture
        DrawTexture(scalpel, currPos.x, currPos.y - scalpel.height, WHITE);

        EndDrawing();

    }

    // Unload textures
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();
}