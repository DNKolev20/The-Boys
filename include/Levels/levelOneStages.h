#include <globals.h>

extern int currentStage;

void stageOne()
{
    Texture2D background = LoadTexture("../res/Level1_images/patient.png");
    const char* text[3] = {
        "Hello doctor in training, today your task will be to \noperate A-Train's heart. [Click Enter to continue]",
        "You will be given instruments for the operation.\n[Click Enter to continue]",
        "You will be guided by your mentor.\n[Click Enter to continue]"
    };
    
    const int fontSize = 32;
    
    Vector2 textSize[3];
    Vector2 textPosition[3];

    for (int i = 0; i < 3; i++)
        textSize[i] = MeasureTextEx(GetFontDefault(), text[i], fontSize, 2.0f);

    for (int i = 0; i < 3; i++)
        textPosition[i] = {GetScreenWidth()/2 - textSize[i].x/2, GetScreenHeight() - textSize[i].y - 200};

    int tutorial = 0;

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

        // Draw
        BeginDrawing();

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        if (tutorial != 3)
            DrawTextEx(GetFontDefault(), text[tutorial], textPosition[tutorial], fontSize, 2.0f, BLACK);

        EndDrawing();

        if (tutorial == 3)
        {
            currentStage++;
            levelOne();
        }

        if (IsKeyPressed(KEY_ENTER) && tutorial < 3)
            tutorial++;
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}

void stageTwo()
{
    Texture2D background = LoadTexture("../res/Level1_images/stage1_pre-cut.png");
    Texture2D scalpel = LoadTexture("../res/scalpel.png");

    Vector2 startPos = { 967, 140 }; // Starting position of image
    Vector2 endPos = { 951, 939 }; // Ending position of image

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

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

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)scalpel.width, (float)scalpel.height }))
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

        Rectangle rect = { position.x, position.y, (float)scalpel.width, (float)scalpel.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            cutAnimation(scalpel, background, startPos, endPos);
            DrawCircleV(startPos, 15, BLUE);
        }
        else
        {
            DrawCircleV(startPos, 15, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        DrawTexture(scalpel, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();
}

void stageThree()
{
    Texture2D background = LoadTexture("../res/Level1_images/cut_wound.png");

    Texture2D retracts[2] = {
        LoadTexture("../res/retractor.png"),
        LoadTexture("../res/retractor.png")
    };

    Vector2 startPos[2] = {
        { 939, 506 },
        { 979, 506 }
    };

    Vector2 position[2] = {
        {0, 0},
        {0, 0}
    };

    Vector2 offset[2] = {
        {0, 0},
        {0, 0}
    };

    bool isDragging[2] = {0, 0};

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
            scale = (float)screenHeight / (float)background.height;
        else 
            scale = (float)screenWidth / (float)background.width;

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

        for (int i = 0; i < 2; i++)
        {
            // Update image 1
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, { position[i].x, position[i].y, (float)retracts[i].width, (float)retracts[i].height }))
                {
                    offset[i] = Vector2Subtract(mousePosition, position[i]);
                    isDragging[i] = true;
                }
            }

            if (isDragging[i] && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePosition = GetMousePosition();
                position[i] = Vector2Subtract(mousePosition, offset[i]);
            }
            else
            {
                isDragging[i] = false;
            } 
        }           

        Rectangle rects[2] = {
            { position[0].x, position[0].y, (float)retracts[0].width, (float)retracts[0].height },
            { position[1].x, position[1].y, (float)retracts[1].width, (float)retracts[1].height }
        };

        bool collidesWithCircle = CheckCollisionCircleRec(startPos[0], 15, rects[0]) && CheckCollisionCircleRec(startPos[1], 15, rects[1]);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        for (int i = 0; i < 2; i++)
            DrawTexture(retracts[i], position[i].x, position[i].y, WHITE);
        

        DrawCircleV(startPos[0], 15, BLUE);
        DrawCircleV(startPos[1], 15, BLUE);

        if (collidesWithCircle)
        {
            currentStage++;
            levelOne();
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();    
}

void stageFour()
{
    Texture2D background = LoadTexture("../res/Level1_images/open_wound.png");
    Texture2D osteotome = LoadTexture("../res/osteotome.png");

    Vector2 circlesPos[3] = {
        {772, 396},
        {794, 563},
        {801, 690}
    }; // Starting positions of the circles

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    bool touchedCircles[3] = {0, 0, 0};

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
            scale = (float)screenHeight / (float)background.height;
        else 
            scale = (float)screenWidth / (float)background.width;

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

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)osteotome.width, (float)osteotome.height }))
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

        Rectangle rect = { position.x, position.y, (float)osteotome.width, (float)osteotome.height };

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        for (int i = 0; i < 3; i++)
        {
            if (CheckCollisionCircleRec(circlesPos[i], 15, rect))
            {
                DrawCircleV(circlesPos[i], 15, GREEN);
                touchedCircles[i] = true;
            }
            else
                DrawCircleV(circlesPos[i], 15, touchedCircles[i] ? GREEN : BLUE);

        }
        
        bool allCirclesTouched = true;
        for (int i = 0; i < 3; i++)
        {
            if (!touchedCircles[i])
            {
                allCirclesTouched = false;
                break;
            }
        }

        DrawTexture(osteotome, position.x, position.y, WHITE);

        if (allCirclesTouched)
        {
            currentStage++;
            levelOne();
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();     
}

void stageFive()
{
    Texture2D background = LoadTexture("../res/Level1_images/open_wound_no_bones.png");
    Texture2D scalpel = LoadTexture("../res/scalpel.png");

    std::vector<std::vector<Vector2>> cutPositions 
    {{
        {{ /*Start position ->*/ { 823, 439 }, { 888, 420 }   /*<- End position*/   }},
        {{ /*Start position ->*/ { 898, 418 }, { 985, 429 }   /*<- End position*/   }},
        {{ /*Start position ->*/ { 1017, 427 }, { 1076, 425 } /*<- End position*/ }},
        {{ /*Start position ->*/ { 1115, 449 }, { 1121, 505 } /*<- End position*/ }}
    }};

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

    int cutVeinArtery = 0;

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
            scale = (float)screenHeight / (float)background.height;
        else 
            scale = (float)screenWidth / (float)background.width;

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

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)scalpel.width, (float)scalpel.height }))
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

        Rectangle scalpelRect = {position.x, position.y, (float)scalpel.width, (float)scalpel.height};

        // Check for collisions between the image and the circles
        for (auto& positions : cutPositions) {
            for (size_t i = 0; i < positions.size(); i += 2) {
                Vector2 circlePos = positions[i];
                if (CheckCollisionCircleRec(circlePos, 5, scalpelRect)) {
                    // Remove the circle and the corresponding line
                    positions.erase(positions.begin() + i, positions.begin() + i + 2);

                    // Reset the position of the scalpel to {0, 0} when it collides with the circle
                    cutVeinArtery++;

                    cutAnimation(scalpel, background, positions[i], positions[i+1]);
                    position = {0, 0};
                    break;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        for (const auto& positions : cutPositions) {
            for (size_t i = 0; i < positions.size(); i += 2) {
                DrawLineEx(positions[i], positions[i + 1], 5, DARKGRAY);
                DrawCircleV(positions[i], 5, BLUE);
            }
        }

        DrawTexture(scalpel, position.x, position.y, WHITE);

        if (cutVeinArtery == 4)
        {
            currentStage++;
            levelOne();
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(scalpel);

    // De-initialization
    CloseWindow();     
}

void stageSix()
{
    Texture2D background = LoadTexture("../res/Level1_images/no_heart.png");
    Texture2D heart = LoadTexture("../res/Level1_images/heart.png");

    Vector2 startPos = { 978, 602 };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

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

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)heart.width, (float)heart.height }))
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

        Rectangle rect = { position.x, position.y, (float)heart.width, (float)heart.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            currentStage++;
            levelOne();
            DrawCircleV(startPos, 15, BLUE);
        }
        else
        {
            DrawCircleV(startPos, 15, BLUE);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            std::cout << GetMousePosition().x << GetMousePosition().y << std::endl;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        DrawTexture(heart, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(heart);

    // De-initialization
    CloseWindow();   
}

void stageSeven()
{
    std::vector<std::vector<Vector2>> cutPositions 
    {{
        {{ /*Start position ->*/ { 823, 439 }, { 888, 420 }   /*<- End position*/   }},
        {{ /*Start position ->*/ { 898, 418 }, { 985, 429 }   /*<- End position*/   }},
        {{ /*Start position ->*/ { 1017, 427 }, { 1076, 425 } /*<- End position*/ }},
        {{ /*Start position ->*/ { 1115, 449 }, { 1121, 505 } /*<- End position*/ }}
    }};

    Texture2D background = LoadTexture("../res/Level1_images/new_heart.png");
    
    // Variables to keep track of time and which background image to use
    float timer = 0.0f;
    int backgroundNum = 0;

    while (!WindowShouldClose())
    {
        timer += GetFrameTime();

        // Get the current screen size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the aspect ratio of the texture and the screen
        float textureRatio = (float)background.height / (float)background.width;
        float screenRatio = (float)screenHeight / (float)screenWidth;

        float scale = 1.0f;

        // Determine the scale factor to maintain aspect ratio and fill the screen
        if (textureRatio > screenRatio) 
            scale = (float)screenHeight / (float)background.height;
        else 
            scale = (float)screenWidth / (float)background.width;

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

            timer += GetFrameTime();
        
        // If 1.5 seconds have passed, change the background image
        if (timer >= 1.5f)
        {
            // Unload the current background image
            UnloadTexture(background);
            
            // Load the next background image
            backgroundNum++;
            if (backgroundNum > 3)
            {
                currentStage++;
                levelOne();
            };   

            char filename[20];
            sprintf(filename, "../res/Level1_images/rib%d.png", backgroundNum);
            background = LoadTexture(filename);
            
            // Reset the timer
            timer = 0.0f;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const auto& positions : cutPositions) {
            for (size_t i = 0; i < positions.size(); i += 2) {
                DrawLineEx(positions[i], positions[i + 1], 5, LIGHTGRAY);
            }
        }

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();    
}

void stageEight()
{
    Texture2D background = LoadTexture("../res/Level1_images/cut_wound.png");
    Texture2D needle = LoadTexture("../res/needle.png");

    Vector2 startPos = { 967, 140 };

    Vector2 position = { 0, 0 };
    Vector2 offset = { 0, 0 };
    bool isDragging = false;

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

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { position.x, position.y, (float)needle.width, (float)needle.height }))
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

        Rectangle rect = { position.x, position.y, (float)needle.width, (float)needle.height };
        if (CheckCollisionCircleRec(startPos, 15, rect))
        {
            currentStage++;
            levelOne();
            DrawCircleV(startPos, 15, BLUE);
        }
        else
        {
            DrawCircleV(startPos, 15, BLUE);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        DrawTexture(needle, position.x, position.y, WHITE);

        DrawCircleV(startPos, 15, BLUE);
        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    UnloadTexture(needle);

    // De-initialization
    CloseWindow();
}

void stageNine()
{
    Texture2D background = LoadTexture("../res/Level1_images/closed_wound.png");

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

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        DrawTextEx(GetFontDefault(), "Press [Enter] to continue", {(float)GetScreenWidth()/2 - 200, (float)GetScreenHeight() - 232}, 32, 2.0f, BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
        {
            currentStage++;
            levelOne();
        }
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}

void stageTen()
{
    Texture2D background = LoadTexture("../res/Level1_images/patient.png");
    const char* text[2] = {
        "Well done! You're on your way to become an excellent surgeon!\n [Click Enter to continue]",
        "Now head onto the next patient.\n[Click Enter to continue]",
    };
    
    const int fontSize = 32;
    
    Vector2 textSize[2];
    Vector2 textPosition[2];

    for (int i = 0; i < 2; i++)
        textSize[i] = MeasureTextEx(GetFontDefault(), text[i], fontSize, 2.0f);

    for (int i = 0; i < 2; i++)
        textPosition[i] = {GetScreenWidth()/2 - textSize[i].x/2, GetScreenHeight() - textSize[i].y - 200};

    int end = 0;

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

        // Draw
        BeginDrawing();

        DrawTexturePro(background, (Rectangle){0, 0, (float)background.width, (float)background.height},
                   (Rectangle){posX, posY, textureWidth, textureHeight}, (Vector2){0, 0}, 0.0f, WHITE);

        if (end != 2)
            DrawTextEx(GetFontDefault(), text[end], textPosition[end], fontSize, 2.0f, BLACK);

        EndDrawing();

        if (end == 2)
        {
            currentLevel++;
            currentStage = 1;
            editLevel("level2");
            menu();
        }

        if (IsKeyPressed(KEY_ENTER) && end < 3)
            end++;
    }

    // Unload textures
    UnloadTexture(background);

    // De-initialization
    CloseWindow();
}