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
    switch(currentLevel)
    {
        case 1:
            levelOne();
            break;
        case 2:
            levelTwo();
            break;
        case 3:
            levelThree();
            break;
    }
}

void moveTexture(Texture2D texture, Vector2& position, Vector2& offset, bool& isDragging)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)texture.width, (float)texture.height }))
        {
            offset = Vector2Subtract(mousePosition, position);
            isDragging = true;
        }
    }

    if (isDragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePosition = GetMousePosition();
        position = Vector2Subtract(mousePosition, offset);
    }
    else
    {
        isDragging = false;
    }
}


void cutAnimation(Texture2D instrument, Texture2D background, Vector2 startPos, Vector2 endPos)
{
    // Define animation variables
    Vector2 currPos = startPos; // Current position of image
    float animationTime = 0.0f; // Time elapsed in animation
    float animationDuration = 2.0f; // Duration of animation in seconds

    while (!WindowShouldClose())
    {

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
            currentStage++;
            switch(currentLevel)
            {
                case 1:
                    levelOne();
                    break;
                case 2:
                    levelTwo();
                    break;
                case 3:
                    levelThree();
                    break;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        backgroundImage(background);

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