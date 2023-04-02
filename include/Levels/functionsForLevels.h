#include <globals.h>

extern int currentStage;

void fadeBetweenStages(float fadeTime) 
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

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
            switch(currentLevel)
            {
                case 1:
                    switch (currentStage)
                    {
                        case 3:
                            currentStage++;
                            levelOne();
                            break;
                    }

                case 2:
                    switch (currentStage)
                    {
                        case 3:
                            currentStage++;
                            levelTwo();
                            break;
                        
                        case 5:
                            currentStage++;
                            levelTwo();
                            break;
                    }

                case 3:
                    switch(currentStage)
                    {
                        case 5:
                            currentStage++;
                            levelThree();
                            break;
                    }
            }

            break;
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

void displayInfoWindow(Texture2D background, Font font)
{
    std::vector<std::string> name = loadItemNames(currentLevel-1, currentStage-1);
    std::vector<std::string> description = loadItemDescription(currentLevel-1, currentStage-1);
    std::vector<Texture2D> textures = loadTextures(currentLevel-1, currentStage-1);
    
    int numImages = textures.size();

    int screenWidth = GetMonitorWidth(0); // get current screen width
    int screenHeight = GetMonitorHeight(0); // get current screen height

    int popupWidth = 800;
    int popupHeight = 500;
    int popupX = (screenWidth - popupWidth) / 2;
    int popupY = (screenHeight - popupHeight) / 2;

    int imageX = popupX + 50;
    int imageY = popupY + 50;
    int textX = imageX + 350;
    int textY = imageY;
    int buttonWidth = 200;
    int buttonHeight = 50;
    int buttonX = popupX + popupWidth - 50 - buttonWidth;
    int buttonY = popupY + popupHeight - 50 - buttonHeight;
    int buttonFontSize = 24;
    int textFontSize = 36;
    int titleFontSize = 48;

    int currentPage = 0;

    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyPressed(KEY_ESCAPE))
            pauseMenu();

        if (IsKeyPressed(KEY_RIGHT) && currentPage < numImages - 1)
            currentPage++;

        if (IsKeyPressed(KEY_LEFT) && currentPage > 0)
            currentPage--;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        backgroundImage(background);

        // Draw popup background
        DrawRectangle(popupX, popupY, popupWidth, popupHeight, Fade(GRAY, 0.7f));
        DrawRectangleLines(popupX, popupY, popupWidth, popupHeight, BLACK);

        if (textures[currentPage].id != 0) 
        {
            DrawTexture(textures[currentPage], imageX, imageY, WHITE);
            DrawTextEx(font, name[currentPage].c_str(), {(float)textX, (float)textY}, textFontSize, 2, BLACK);
            DrawTextEx(font, description[currentPage].c_str(), {(float)textX, float(textY + textFontSize + 20)}, textFontSize, 2, BLACK);
        }
        else
        {
            Vector2 nameSize = MeasureTextEx(font, name[currentPage].c_str(), textFontSize, 1);
            int nameX = popupX + (popupWidth - nameSize.x) / 2;
            int nameY = popupY + (popupHeight - nameSize.y) / 2 - 120;
            DrawTextEx(font, name[currentPage].c_str(), {(float)nameX, (float)nameY}, textFontSize, 2, BLACK);

            Vector2 descriptionSize = MeasureTextEx(font, description[currentPage].c_str(), textFontSize, 1);
            int descriptionX = popupX + (popupWidth - descriptionSize.x) / 2;
            int descriptionY = popupY + (popupHeight - descriptionSize.y) / 2 - 70;
            DrawTextEx(font, description[currentPage].c_str(), {(float)descriptionX, float(descriptionY + textFontSize + 20)}, textFontSize, 2, BLACK);    
        }

        // Draw button
        if (CheckCollisionPointRec(GetMousePosition(), { (float)buttonX, (float)buttonY, (float)buttonWidth, (float)buttonHeight }))
        {
            DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, LIGHTGRAY);
            DrawTextEx(font, "Close", {float(buttonX + 20), float(buttonY + 10)}, buttonFontSize, 2, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                break;
        }
        else
        {
            DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, GRAY);
            DrawTextEx(font, "Close", {float(buttonX + 20), float(buttonY + 10)}, buttonFontSize, 2, BLACK);
        }

        // Draw page number
        DrawTextEx(font, TextFormat("%d/%d", currentPage + 1, numImages), {float(popupX + popupWidth - 100), float(popupY + popupHeight - 40)}, titleFontSize, 2, BLACK);

        EndDrawing();
    }

    return;
}