#include <globals.h>

extern int currentStage;

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

void cutAnimation(Texture2D instrument, Texture2D background, Vector2 startPos, Vector2 endPos)
{
    // Define animation variables
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

        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pauseMenu();    
        }

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

            switch (currentStage)
            {
                case 3:
                    currentStage++;
                    levelOne();
                    break;
            }
            
            break;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        // Draw texture
        DrawTexture(instrument, currPos.x, currPos.y - instrument.height, WHITE);

        EndDrawing();

    }

}

void editLevel(std::string level) 
{
    std::ifstream infile("savefile.txt");
    std::string line;
    std::ofstream outfile("temp.txt");

    while (getline(infile, line)) {
        if (line.substr(0, level.length()) == level) {
            line.replace(line.find("=") + 2, 1, "1");
        }
        outfile << line << std::endl;
    }

    infile.close();
    outfile.close();
    remove("savefile.txt");
    rename("temp.txt", "savefile.txt");
}